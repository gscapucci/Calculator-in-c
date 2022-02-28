#include "calculator.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <float.h>

#include "stack.h"
#include "string_vector.h"

bool check_syntax(char *str);
char *remove_spaces(char* s);

enum SYMBOLS 
{
    ADDITION = '+',
    SUBTRACTION = '-',
    MULTIPLICATION = '*',
    DIVISION = '/',
    OPEN_PARENTHESIS = '(',
    CLOSE_PARENTHESIS = ')',
    DOT = '.'
};

bool is_symbol(char c)
{
    switch (c)
    {
    case ADDITION:
    case SUBTRACTION:
    case MULTIPLICATION:
    case DIVISION:
    case OPEN_PARENTHESIS:
    case CLOSE_PARENTHESIS:
        return true;
    default:
        return false;
    }
}

bool is_operator(c)
{
    switch (c)
    {
    case ADDITION:
    case SUBTRACTION:
    case MULTIPLICATION:
    case DIVISION:
        return true;
    default:
        return false;
    }
}

int weight(char c)
{
    switch (c)
    {
    case ADDITION:
    case SUBTRACTION:
        return 1;
    case MULTIPLICATION:
    case DIVISION:
        return 2;
    default:
        return -1;
    }
}

struct Calculator 
{
    Str_vector *parsed_expression;
    long double result;
};

Calculator *create_calculator()
{
    Calculator *calc = (Calculator *)malloc(sizeof(Calculator));
    if(calc)
    {
        calc->parsed_expression = create_vector(20);
        calc->result = 0;
        return calc;
    }
    return NULL;
}

size_t get_expression_size(Calculator *calculator)
{
    return get_vector_size(calculator->parsed_expression);
}

size_t get_expression_lengh(Calculator *calculator)
{
    return sum_of_string_lengh(calculator->parsed_expression);
}

bool check_syntax(char *str)
{
    size_t str_lengh = strlen(str);
    int parenthesis_count = 0;
    int dot_count = 0;
    for (size_t i = 0; i < str_lengh; i++)
    {
        if(is_symbol(str[i]))
        {
            dot_count = 0;
        }
        if(str[i] == DOT)
        {
            if(is_symbol(str[i - 1]) || is_symbol(str[i + 1]))
            {
                return false;
            }
            dot_count++;
            if(dot_count >= 2)
            {
                return false;
            }
        }
        if(str[i] == OPEN_PARENTHESIS)
        {
            if(i != str_lengh - 1 && str[i + 1] == CLOSE_PARENTHESIS)
            {
                return false;
            }
            if(i != 0)
            {
                if(!is_symbol(str[i - 1]))
                {
                    return false;
                }
            }
            parenthesis_count++;
        }
        if(str[i] == CLOSE_PARENTHESIS)
        {
            if(i != str_lengh - 1)
            {
                if(!is_symbol(str[i + 1]))
                {
                    return false;
                }
            }
            parenthesis_count--;
        }
        if(parenthesis_count < 0)
        {
            return false;
        }
    }
    if(parenthesis_count != 0)
    {
        return false;
    }
    return true;
}

char *remove_spaces(char* s)
{
    size_t count = 0;
    for (size_t i = 0; i < strlen(s); i++)
    {
        if(s[i] == ' ')
            count++;
    }
    size_t size = strlen(s) - count + 1;
    char *str = (char *)malloc(size * sizeof(char));
    for (size_t i = 0, j = 0; i < strlen(s); i++)
    {
        if(s[i] != ' ')
        {
            str[j] = s[i];
            j++;
        }
    }
    str[size-1] = '\0';
    return str;
}

char* take_next(char **expression)
{
    static bool revers_next_number_sign = false;
    if(*expression == NULL)
    {
        return NULL;
    }
    char *str = NULL;
    while (strlen(*expression) > 0)
    {
        if(is_symbol((*expression)[0]))
        {
            if(strlen(*expression) > 1 && (*expression)[1] == SUBTRACTION)
            {
                revers_next_number_sign = !revers_next_number_sign;
                memmove(*expression, *expression + 1, strlen(*expression) * sizeof(char));
            }
            else if(str == NULL)
            {
                str = (char *)malloc(2 * sizeof(char));
                str[0] = (*expression)[0];
                str[1] = '\0';
                memmove(*expression, *expression + 1, strlen(*expression) * sizeof(char));
                return str;
            }
        }
        else
        {
            if(str == NULL)
            {
                if(revers_next_number_sign)
                {
                    revers_next_number_sign = false;
                    str = (char *)malloc(2 * sizeof(char));
                    str[0] = '-';
                    str[1] = '\0';
                }
                else
                {
                    str = (char *)malloc(sizeof(char));
                    str[0] = '\0';
                }
            }
            strncat(str, (*expression), 1);
            memmove(*expression, *expression + 1, strlen(*expression) * sizeof(char));
        }
    }
    if(str == NULL)
    {
        return NULL;
    }
    return str;
}

Str_vector *parse_expression(char *expression)
{
    Str_vector *vector = create_vector(20);
    char *substr;
    while (strlen(expression) > 0)
    {
        substr = take_next(&expression);
        push_back(vector, substr);
        free(substr);
    }
    return vector;
}

long double solve(Str_vector *vec)
{
/*  - A - (- (- B - C + D)) * (E + F) - G
stack:  - - -
RPN:    A BCDEF G

RPN:    A B C * D + E F + * G - -
- both simbols and numbers(long double)
*/
    Stack *stack = create_Stack();
    RPN *rpn_stack = create_RPN();
    char *str = NULL;
    while (get_vector_size(vec) > 0)
    {
        str = get_at(vec, 0);
        pop_front(vec);
        if(is_symbol(str))
        {
            if(weight(str[0]) < weight(stack_get_top(stack)))
            {
                RPN_push_back(rpn_stack, false, str[0]);
                stack_pop_back(stack);
            }
            stack_push_back(stack, str);
            if(str[0] == CLOSE_PARENTHESIS)
            {
                solve_parenthesis(&rpn_stack);
            }
        }
        char c = RPN_get_top_char(rpn_stack);
        long double num1 = 0, num2 = 0;
        if(is_operator(c))
        {
            RPN_pop_back(rpn_stack);

            num1 = RPN_get_top_number(rpn_stack);
            RPN_pop_back(rpn_stack);

            num2 = RPN_get_top_number(rpn_stack);
            RPN_pop_back(rpn_stack);

            switch (c)
            {
            case ADDITION:
                num1 += num2;
                break;
            case SUBTRACTION:
                num1 -= num2;
                break;
            case MULTIPLICATION:
                num1 *= num2;
                break;
            case DIVISION:
                num1 /= num2;
                break;
            default:
                break;
            }
        }
        free(str);
    }
    free_stack(stack);
    free_RPN(rpn_stack);
    return 0.0l;
}

void calculate(Calculator *calculator, char *str)
{
    char *expression = remove_spaces(str);
    if(!check_syntax(expression))
    {
        fprintf(stderr, "Invalid expression: \"%s\" is invalid", expression);
        free(expression);
        return;
    }
    calculator->parsed_expression = parse_expression(expression);
    long double solution = solve(calculator->parsed_expression);
    print_vec(calculator->parsed_expression);
    free(expression);
}
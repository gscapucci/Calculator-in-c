#include "stack.h"
/* A - (B * C + D) * (E + F) - G
stack:
- only simbols
RPN:    A B C * D + E F + * G - -
- both simbols and numbers
*/

#include <stdio.h>
#include <errno.h>

struct Stack
{
    size_t size, capacity;
    char *values;
};

Stack* create_Stack()
{
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if(stack)
    {
        stack->capacity = 10;
        stack->size = 0;
        stack->values = (char *)malloc(10 * sizeof(char));
        if(stack->values)
        {
            return stack;
        }
        free(stack);
        return NULL;
    }
    return NULL;
}

void stack_push(Stack *symbols_stack, char symbol)
{
    if(symbols_stack)
    {
        symbols_stack->values[symbols_stack->size++] = symbol;
        if(symbols_stack->size >= symbols_stack->capacity)
        {
            symbols_stack->values = (char *)realloc(symbols_stack->values, symbols_stack->capacity * 2);
        }
    }
}

void stack_pop(Stack *symbols_stack)
{
    if(symbols_stack)
    {
        if(symbols_stack->size == 0)
        {
            fprintf(stderr, "stack underflow\n");
            return;
        }
        symbols_stack->size--;
        if(symbols_stack->size < symbols_stack->capacity / 2 && symbols_stack->size >= 20)
        {
            symbols_stack->values = (char *)realloc(symbols_stack->values, symbols_stack->capacity / 2);
        }
    }
}

void free_stack(Stack *symbols_stack)
{
    if(symbols_stack)
    {
        if(symbols_stack->values)
        {
            free(symbols_stack->values);
        }
        free(symbols_stack);
    }
}

char stack_get_top(Stack *symbols_stack)
{
    if(symbols_stack)
    {
        if(symbols_stack->values)
        {
            if(symbols_stack->size > 0)
            {
                return symbols_stack->values[symbols_stack->size - 1];
            }
        }
    }
    return '\0';
}

typedef struct RPN_Node RPN_Node;

struct RPN_Node
{
    bool *is_operator;
    union
    {
        long double number;
        char operator;
    };
};

struct RPN
{
    size_t size, capacity;
    RPN_Node *values;
};

RPN *create_RPN()
{
    RPN *stack = (RPN *)malloc(sizeof(RPN));
    if(stack)
    {
        stack->capacity = 10;
        stack->size = 0;
        stack->values = (RPN_Node *)malloc(10 * sizeof(RPN_Node));
        if(stack->values)
        {
            for (size_t i = 0; i < stack->size; i++)
            {
                stack->values[i].is_operator = NULL;
            }
            return stack;
        }
        free(stack);
    }
    return NULL;
}


void RPN_push(RPN *rpn_stack, bool is_num, char *num_or_symbol)
{
    if(rpn_stack)
    {
        if(rpn_stack->values)
        {
            if(rpn_stack->values[rpn_stack->size].is_operator == NULL)
            {
                rpn_stack->values[rpn_stack->size].is_operator = (bool *)malloc(sizeof(bool));
                if(rpn_stack->values[rpn_stack->size].is_operator != NULL)
                {
                    if(is_num)
                    {
                        *(rpn_stack->values[rpn_stack->size].is_operator) = false;
                        rpn_stack->values[rpn_stack->size].number = strtold(num_or_symbol, NULL);
                    }
                    else
                    {
                        *(rpn_stack->values[rpn_stack->size].is_operator) = true;
                        rpn_stack->values[rpn_stack->size].operator = *num_or_symbol;
                    }
                    rpn_stack->size++;
                    if(rpn_stack->size >= rpn_stack->capacity)
                    {
                        rpn_stack->values = (RPN_Node *)realloc(rpn_stack->values, rpn_stack->capacity * 2);
                    }
                }
                else
                {
                    fprintf(stderr, "push back error");
                }
            }
        }
    }
}

void RPN_pop(RPN *rpn_stack)
{
    if(rpn_stack)
    {
        if(rpn_stack->size == 0)
        {
            fprintf(stderr, "stack underflow");
        }
        free(rpn_stack->values[rpn_stack->size].is_operator);
        rpn_stack->size--;
        if(rpn_stack->size < rpn_stack->capacity / 2)
        {
            rpn_stack->values = (RPN_Node *)realloc(rpn_stack->values, rpn_stack->capacity / 2);
        }
    }
}

size_t RPN_get_number_of_numbers(RPN *rpn_stack)
{
    size_t sum = 0;
    if(rpn_stack)
    {
        for (size_t i = 0; i < rpn_stack->size; i++)
        {
            if(*(rpn_stack->values[i].is_operator) == false)
            {
                sum++;
            }
        }
    }
    return sum;
}

char RPN_get_top_char(RPN *rpn_stack)
{
    if(rpn_stack)
    {
        if(rpn_stack->values)
        {
            if(*(rpn_stack->values[rpn_stack->size -1 ].is_operator) == true)
            {
                return rpn_stack->values[rpn_stack->size - 1].operator;
            }
        }
    }
    return '\0';
}

void free_RPN(RPN *rpn_stack)
{
    if(rpn_stack)
    {
        if(rpn_stack->values)
        {
            for (size_t i = 0; i < rpn_stack->size; i++)
            {
                if(rpn_stack->values[i].is_operator)
                {
                    free(rpn_stack->values[i].is_operator);
                }
            }
            free(rpn_stack->values);
        }
        free(rpn_stack);
    }
}
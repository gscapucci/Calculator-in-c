#ifndef STACK_H
#define STACK_H
/* A - (B * C + D) * (E + F) - G
stack:  - -
- only simbols
RPN:    A B C * D + E F + * G - -
- both simbols and numbers(long double)
*/

#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack Stack;
typedef struct RPN RPN;

Stack* create_Stack();
void stack_push(Stack *symbols_stack, char symbol);
void stack_pop(Stack *symbols_stack);
void free_stack(Stack *symbols_stack);
char stack_get_top(Stack *symbols_stack);

RPN* create_RPN();
void RPN_push(RPN *rpn_stack, bool is_num, char *num_or_symbol);
void RPN_pop(RPN *rpn_stack);
size_t RPN_get_number_of_numbers(RPN *rpn_stack);
char RPN_get_top_char(RPN *rpn_stack);
long double RPN_get_top_number(RPN *rpn_stack);
void free_RPN(RPN *rpn_stack);
#endif /* STACK_H */
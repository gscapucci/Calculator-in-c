#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdlib.h>

typedef struct Calculator Calculator;

Calculator *create_calculator();
size_t get_expression_size(Calculator *calculator);
size_t get_expression_lengh(Calculator *calculator);
void calculate(Calculator *calculator, char *expression);
#endif /* CALCULATOR_H */
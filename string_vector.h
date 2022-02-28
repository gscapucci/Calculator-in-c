#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

typedef struct Str_vector Str_vector;

Str_vector* create_vector(size_t start_capacity);
void push_back(Str_vector *vec, char *str);
void pop_back(Str_vector *vec);
void pop_front(Str_vector *vec);
void print_vec(Str_vector *vec);
char* get_at(Str_vector *vec, size_t pos);
size_t get_vector_size(Str_vector *vec);
size_t sum_of_string_lengh(Str_vector *vec);
void free_vector(Str_vector *vec);
#endif /* STRING_VECTOR_H */
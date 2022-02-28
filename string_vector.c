#include "string_vector.h"

struct Str_vector
{
    char **values;
    size_t capacity, size;
};

Str_vector* create_vector(size_t start_capacity)
{
    Str_vector *vec = (Str_vector *)malloc(sizeof(Str_vector));
    if(vec)
    {
        vec->capacity = start_capacity;
        vec->size = 0;
        vec->values = (char **)malloc(start_capacity * sizeof(char *));
        for (size_t i = 0; i < start_capacity; i++)
        {
            vec->values[i] = NULL;
        }
        return vec;
    }
    return NULL;
}

void push_back(Str_vector *vec, char *str)
{
    if(!strlen(str) || !str || !vec || !vec->values)
    {
        fprintf(stderr, "vector was not create\n");
        return;
    }
    if(vec->size == vec->capacity)
    {
        vec->values = (char **)realloc(vec->values, vec->capacity * 2);
    }

    vec->values[vec->size] = (char *)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(vec->values[vec->size], str);
    vec->size++;
}

void pop_front(Str_vector *vec)
{
    if(vec)
    {
        if(vec->values)
        {
            if(vec->size > 0)
            {
                memmove(vec->values, vec->values + 1, vec->size * sizeof(char *));
                vec->capacity--;
                vec->size--;
                if(vec->size <= vec->capacity / 2)
                {
                    vec->values = (char **)realloc(vec->values, vec->capacity / 2);
                }
                else if (vec->capacity <= 10)
                {
                    vec->values = (char **)realloc(vec->values, 10 * sizeof(char *));
                }
            }
        }
    }
}

void pop_back(Str_vector *vec)
{
    if(vec->size == 0)
    {
        fprintf(stderr, "Size can not be less then 0");
        return;
    }
    vec->size--;
    free(vec->values[vec->size]);
    vec->values[vec->size] = NULL;
    if(vec->size <= vec->capacity / 2 && vec->capacity > 10)
    {
        vec->values = (char **)realloc(vec->values, vec->capacity / 2);
    }

}

void print_vec(Str_vector *vec)
{
    for (size_t i = 0; i < vec->size; i++)
    {
        printf("%s\n", vec->values[i]);
    }
}

char* get_at(Str_vector *vec, size_t pos)
{
    if (vec)
    {
        if(vec->values)
        {
            if(pos < vec->size)
            {
                return vec->values[pos];
            }
        }
    }
    return NULL;
}

size_t get_vector_size(Str_vector *vec)
{
    return vec->size;
}

size_t sum_of_string_lengh(Str_vector *vec)
{
    size_t sum = 0;
    for (size_t i = 0; i < vec->size; i++)
    {
        sum += strlen(vec->values[i]);
    }
    return sum;
}

void free_vector(Str_vector *vec)
{
    if(vec)
    {
        if (vec->values)
        {
            for (size_t i = 0; i < vec->size; i++)
            {
                free(vec->values[i]);
            }
            free(vec->values);
        }
        free(vec);
    }
}
#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    double * data;
    int size;
} vector_t;

int vector_init(vector_t * vect, int size);
int vector_print(vector_t * vect);
int vector_merge(vector_t * vect_1, vector_t * vect_2);


#endif // MAIN_H

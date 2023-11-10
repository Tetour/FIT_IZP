#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct {
    bool x;
    bool y;
    char * s;
    int n;
} config_t;

typedef struct {
    double * data;
    int size;
} vector_t;

int initVector(vector_t * vect, int size);

int parseArg(int argc, char ** argv);

void printCfg(config_t conf);

void printArr(int * arr, int size);
void multiArr(int * arr, int size, int multi);


#endif // MAIN_H

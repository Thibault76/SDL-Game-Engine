#pragma once
#include <math.h>
#include <stdarg.h>

typedef struct Vector{
    float *value;
    int nbDiemsions;
} Vector;

typedef Vector Point;

Vector *EngineMathsNewVector(int num, ...);

Vector *EngineMathsFreeVector(Vector *v);

void printVector(Vector *v);
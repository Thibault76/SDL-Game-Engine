#include "engine/maths.h"
#include <stdlib.h>
#include <stdio.h>
#include "engine/core.h"

Vector *EngineMathsNewVector(int num, ...){
    va_list valist;
    va_list copy;
    va_start(valist, num);
    va_copy(copy, valist);

    Vector *v;
    v = malloc(sizeof(Vector));
    MALLOC_CHECK(v);

    v->nbDiemsions = num;
    v->value = malloc(sizeof(float) * num);
    MALLOC_CHECK(v->value);
    
    for(int i = 0; i < num; i++){
        v->value[i] = va_arg(valist, double);
    }
    va_end(valist);

    for(int i = 0; i < num; i++){
        int intV = va_arg(copy, int);
        if(v->value[i] == (float)0){
            v->value[i] = intV;
        }
    }
    va_end(copy);

    return v;
}

Vector *EngineMathsFreeVector(Vector *v){
    free(v->value);
    free(v);

    return NULL;
}

void printVector(Vector *v){
    printf("\n----------------\nVector: ");
    for(int i = 0; i < v->nbDiemsions; i++){
        printf("[%f], ", v->value[i]);
    }
    printf("\n----------------\n");
}
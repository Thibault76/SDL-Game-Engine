#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;

typedef enum {false, true} Bool;

#define BIT(x) (1 << x)
#define MALLOC_CHECK(x) if (!x){fprintf(stderr, "malloc Error"); exit(EXIT_FAILURE);}
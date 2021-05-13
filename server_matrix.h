#ifndef SERVER_MATRIX_H_
#define SERVER_MATRIX_H_

#include <stdlib.h>
#include "common_mod26.h"

#define MATRIX_MAX_SIZE 4

typedef struct matrix_t {
    mod26 values[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
    int x;
    int y;
} matrix;

void matrix_init(matrix *this, int x, int y);

void matrix_uninit(matrix *this);

mod26 matrix_get(matrix this, int x, int y);

void matrix_set(matrix *this, int x, int y, mod26 value);

void matrix_setFromArray(matrix *this, const char *values, const int l);

void matrix_multiply(matrix *result, matrix matrix_a, matrix matrix_b);

#endif  // SERVER_MATRIX_H_

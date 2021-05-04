#ifndef COMMON_MATRIX_H_
#define COMMON_MATRIX_H_

#include <stdlib.h>
#include "server_mod26.h"

typedef struct matrix_t {
    mod26 **values;
    int x;
    int y;
} matrix;

int matrix_create(matrix *this, int x, int y);

int matrix_delete(matrix *this);

int matrix_get(matrix this, int x, int y);

int matrix_set(matrix *this, int x, int y, mod26 value);

int matrix_multiply(matrix *result, matrix matrix_a, matrix matrix_b);

#endif  // COMMON_MATRIX_H_

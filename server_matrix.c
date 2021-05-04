#include "server_matrix.h"
#include <stdio.h>

// x: filas
// y: columnas

int matrix_create(matrix *this, int x, int y) {
  if (!this) {
      return 1;
  }

  if ((this->values = (mod26**) malloc(x * sizeof(mod26*))) == NULL) {
    return 1;
  }
  this->x = x;

  for (int i = 0; i < x; i++) {
    if ((this->values[i] = (mod26 *)calloc(y, sizeof(mod26))) == NULL) {
      matrix_delete(this);
      return 1;
    }
    this->y++;
  }
  this->y = y;
  return 0;
}

int matrix_delete(matrix *this) {
  if (!this) {
    return 0;
  }
  for (int i = 0; i < this->x; i++) {
    free((this->values)[i]);
  }
  free(this->values);
  this->values = NULL;
  this->y = 0;
  this->x = 0;

  return 0;
}

int matrix_get(matrix this, int x, int y) {
  if (this.x <= x || this.y <= y) {
    return -1;
  }

  return this.values[x][y];
}

int matrix_set(matrix this, int x, int y, mod26 value) {
  if (this.x <= x || this.y <= y) {
    return -1;
  }
  this.values[x][y] = value;

  return 0;
}


int matrix_multiply(matrix *result, matrix matrix_a, matrix matrix_b) {
  mod26 a = 0, b = 0, mult = 0;
  int i, j, k;
  if (matrix_create(result, matrix_a.x, matrix_b.y)) {
    return 1;
  }

  for (i = 0; i < matrix_a.x; i++) {
    for (j = 0; j < matrix_b.y; j++) {
      for (k = 0; k < matrix_a.y; k++) {
        a = matrix_get(matrix_a, i, k);
        b = matrix_get(matrix_b, k, j);
        mult = mod26_multiply(a, b);
        matrix_set(*result, i, j, mod26_sum(result->values[i][j], mult));
      }
    }
  }

  return 0;
}

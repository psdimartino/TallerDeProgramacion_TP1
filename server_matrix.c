#include <stdio.h>
#include "server_matrix.h"
#include "common_error.h"

void matrix_init(matrix *this, const int x, const int y) {
  this->y = y;
  this->x = x;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      matrix_set(this, i, j, mod26_init('A'));
    }
  }
}

void matrix_uninit(matrix *this) {
  this->y = 0;
  this->x = 0;
}

mod26 matrix_get(matrix this, int x, int y) {
  if (this.x <= x || this.y <= y) {
    error_exit_msg("Out of range in matrix_get");
  }

  return this.values[x][y];
}

void matrix_set(matrix *this, int x, int y, mod26 value) {
  if (this->x <= x || this->y <= y) {
    error_exit_msg("Out of range in matrix_set");
  }
  this->values[x][y] = value;
}

void matrix_setFromArray(matrix *this, const char *values, const int l) {
  for (int i = 0, key_pos = 0; i < this->x; i++) {
      for (int j = 0; j < this->y; j++, key_pos++) {
          if (key_pos < l) {
              matrix_set(this, i, j, mod26_init(values[key_pos]));
          } else {
              matrix_set(this, i, j, mod26_init('A'));
          }
      }
  }
}

void matrix_multiply(matrix *res, const matrix mat_a, const matrix mat_b) {
  matrix_init(res, mat_a.x, mat_b.y);

  mod26 aux = mod26_init('A');
  for (int i = 0; i < mat_a.x; i++) {
    for (int j = 0; j < mat_b.y; j++) {
      for (int k = 0; k < mat_a.y; k++) {
        mod26 a = matrix_get(mat_a, i, k);
        mod26 b = matrix_get(mat_b, k, j);
        mod26 mult = mod26_multiply(a, b);
        aux = mod26_sum(aux, mult);
      }
      matrix_set(res, i, j, aux);
      aux = mod26_init('A');
    }
  }
}

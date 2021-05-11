#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "server_encoder.h"
#include "server_matrix.h"
#include "common_mod26.h"

#define MAX_LEN 16
#define ROUND_UP(A, B) (A - (A % B) + B)

void encoder_setMatrixWithString(matrix mat, string input) {
    int key_pos = 0;
    int input_len = strlen((char *)input);
    for (int i = 0; i < mat.x; i++) {
        for (int j = 0; j < mat.y; j++, key_pos++) {
            if (key_pos < input_len) {
                matrix_set(&mat, i, j, mod26_createFromChar(input[key_pos]));
            } else {
                matrix_set(&mat, i, j, mod26_create(0));
            }
        }
    }
}

int encoder_create(encoder* self, string key) {
    self->vector_len = sqrt(strlen((char *)key));
    matrix_create(&(self->key), self->vector_len, self->vector_len);
    encoder_setMatrixWithString(self->key, key);
    return 0;
}

// void encoder_getStringFromMatrix(string output, matrix input) {
//     int key_pos = 0;
//     for (int i = 0; i < input.x; i++) {
//         for (int j = 0; j < input.y; j++, key_pos++) {
//             output[key_pos] = mod26_getChar(matrix_get(input, i, j));
//         }
//     }
// }

void curateInput(char *input) {
    int next = 0, i = 0;
    for (i = next = 0; input[i]; i++) {
        if (isupper(input[i])) {
            input[next++] = input[i];
        }
    }
    input[next] = '\0';
}

int encoder_encode(encoder *self, string input, int **output, int *l) {
    matrix inputVector, outputVector;
    curateInput(input);
<<<<<<< Updated upstream
=======
    printf("INPUT <%s>\n", input);
    *l = ROUND_UP(strlen(input), self->vector_len);
    matrix_create(&inputVector, self->vector_len, 1);
    *output = calloc(*l, sizeof(int));
    // printf("input <%s>, len = %lu\n", input, strlen(input));
>>>>>>> Stashed changes
    for (int i = 0; i < strlen(input); i+=self->vector_len) {
        encoder_setMatrixWithString(inputVector, &input[i]);
        matrix_multiply(&outputVector, self->key, inputVector);
        for (int j = i % self->vector_len; j < self->vector_len; j++) {
            (*output)[i + j] = matrix_get(outputVector, j , 0);
            // printf("i:[%d] j: [%d]=%d\n", i, j, (*output)[i + j]);
        }
        matrix_delete(&outputVector);
        // printf("out i:[%d]\n", i);
    }
    matrix_delete(&inputVector);
    return 0;
}

int encoder_destroy(encoder* self) {
    return matrix_delete(&(self->key));
}

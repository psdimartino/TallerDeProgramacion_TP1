#include <stdio.h>
#include <math.h>
#include <string.h>
#include "server_encoder.h"
#include "server_matrix.h"
#include "server_mod26.h"

#define MAX_LEN 16
#define ROUND_UP(A, B) (A - (A % B) + B)

void print_matrix(matrix input) {
    for (int i = 0; i < input.x; i++) {
        for (int j = 0; j < input.y; j++) {
            printf("%d", matrix_get(input, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

void encoder_setMatrixWithString(matrix mat, string input) {
    int key_pos = 0;
    int input_len = strlen((char *)input);
    for (int i = 0; i < mat.x; i++) {
        for (int j = 0; j < mat.y; j++, key_pos++) {
            if (key_pos < input_len) {
                matrix_set(mat, i, j, mod26_createFromChar(input[key_pos]));
            } else {
                matrix_set(mat, i, j, mod26_create(0));
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

void encoder_getStringFromMatrix(string output, matrix input) {
    int key_pos = 0;
    for (int i = 0; i < input.x; i++) {
        for (int j = 0; j < input.y; j++, key_pos++) {
            output[key_pos] = mod26_getChar(matrix_get(input, i, j));
        }
    }
}

int encoder_encode(encoder *self, string input, string *output) {
    matrix inputVector, outputVector;
    char *auxString = calloc(self->vector_len, sizeof(char));
    int outputSize = ROUND_UP(strlen(input), self->vector_len);
    matrix_create(&inputVector, self->vector_len, 1);
    *output = calloc(outputSize + 1, sizeof(char));

    for (int i = 0; i < strlen((char *)input); i+=self->vector_len) {
        encoder_setMatrixWithString(inputVector, &input[i]);
        matrix_multiply(&outputVector, self->key, inputVector);
        encoder_getStringFromMatrix(auxString, outputVector);
        strncat(*output, auxString, self->vector_len);
        matrix_delete(&outputVector);
    }
    matrix_delete(&inputVector);
    free(auxString);
    return 0;
}

int encoder_destroy(encoder* self) {
    return matrix_delete(&(self->key));
}

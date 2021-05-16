#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "server_encoder.h"
#include "server_matrix.h"
#include "common_mod26.h"
#include "common_error.h"

#define ROUND_UP(A, B) ((A + B - 1) / B) * B
#define MIN(A, B) ((A) < (B) ? (A) : (B))

void encoder_init(encoder* this, const char* key) {
    this->vector_len = sqrt(strlen(key));
    matrix_init(&(this->key), this->vector_len, this->vector_len);
    matrix_setFromArray(&(this->key), key, strlen(key));
}

void curateInput(char *input) {
    int next = 0, i = 0;
    for (i = next = 0; input[i]; i++) {
        if (isupper(input[i])) {
            input[next++] = input[i];
        }
    }
    input[next] = '\0';
}

void encoder_encode(encoder *this, char* input, mod26 *output, uint16_t *l) {
    matrix inputVector, resultVector;
    curateInput(input);
    int inputLen = strlen(input);

    *l = ROUND_UP(inputLen, this->vector_len);
    matrix_init(&inputVector, this->vector_len, 1);

    for (int i = 0; i < inputLen; i+=this->vector_len) {
        matrix_setFromArray(&inputVector, &input[i],
                             MIN(this->vector_len, inputLen - i));
        matrix_multiply(&resultVector, this->key, inputVector);
        for (int j = i % this->vector_len; j < this->vector_len; j++) {
            output[i + j] = matrix_get(resultVector, j , 0);
        }
        matrix_uninit(&resultVector);
    }
    output[*l] = '\0';
    matrix_uninit(&inputVector);
}

void encoder_uninit(encoder* this) {
    matrix_uninit(&(this->key));
}

#ifndef SERVER_ENCODER_H_
#define SERVER_ENCODER_H_
#include <stdlib.h>
#include "server_matrix.h"

typedef char* string;

typedef struct encoder_t {
    matrix key;
    int vector_len;
} encoder;  

int encoder_create(encoder* self, string key);

int encoder_encode(encoder *self, string input, string *output);

int encoder_destroy(encoder* self);

#endif  // SERVER_ENCODER_H_

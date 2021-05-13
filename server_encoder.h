#ifndef SERVER_ENCODER_H_
#define SERVER_ENCODER_H_
#include <stdlib.h>
#include "server_matrix.h"
#include "common_mod26.h"

typedef struct encoder_t {
    matrix key;
    int vector_len;
} encoder;  

void encoder_init(encoder* this, char* key);

void encoder_encode(encoder *this, char* input, mod26 *output, int *l);

void encoder_uninit(encoder* this);

#endif  // SERVER_ENCODER_H_

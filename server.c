#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "common_socket.h"
#include "server_encoder.h"
#include "common_mod26.h"

#define MAX_LENGTH (16*16)-1

int main(int argc, char *argv[]) {
    encoder hill;
    socket_t skt;
    char input[MAX_LENGTH] = {0};
    mod26 output[MAX_LENGTH] = {0};
    int l = 0;
    encoder_init(&hill, argv[2]);
    socket_init(&skt);
    socket_bind(&skt, argv[1]/*servicename*/);
    socket_listen(&skt);
    socket_accept(&skt);
    while (socket_read(&skt, input)) {
        encoder_encode(&hill, input, output, &l);
        socket_send(&skt, (char *)output, l);
    }
    socket_uninit(&skt);
    encoder_uninit(&hill);
    return(EXIT_SUCCESS);
}

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "common_socket.h"
#include "server_encoder.h"

int main(int argc, char *argv[]) {
    encoder hill;
    socket_t skt;
    char *input = NULL;
    char *output;
    encoder_create(&hill, argv[2]);
    if ( socket_init(&skt) ) {
        fprintf(stderr, "socket_init failed\n");
        return 1;
    }
    if ( socket_bind(&skt, argv[1]/*servicename*/) ) {
        fprintf(stderr, "socket_bind failed\n");
        return 1;
    }
    if ( socket_listen(&skt) ) {
        fprintf(stderr, "socket_listen failed\n");
        socket_uninit(&skt);
        return 1;
    }
    if ( socket_accept(&skt) ) {
        fprintf(stderr, "socket_accept failed\n");
        socket_uninit(&skt);
        return 1;
    }
    while ((socket_read_string(&skt, &input)) != 1) {
        encoder_encode(&hill, input, &output);
        if ( (socket_send_string(&skt, output)) == -1 ) {
            fprintf(stderr, "socket_read failed\n");
            socket_uninit(&skt);
            return 1;
        }
        free(input);
        free(output);
        output = NULL;
        input = NULL;
    }
    if ( socket_uninit(&skt) ) {
        fprintf(stderr, "socket_uninit failed\n");
        return 1;
    }
    encoder_destroy(&hill);
    return 0;
}

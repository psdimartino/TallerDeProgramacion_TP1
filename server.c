#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common_socket.h"
#include "server_encoder.h"

void curateString(char *s) {
    int writer = 0, reader = 0;

    while (s[reader]) {
        if (isupper(s[reader])) {
            s[writer++] = s[reader];
        }
        reader++;
    }
    s[writer] = 0;
}

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
        // printf("recived: <%s>\n", input);
        curateString(input);
        encoder_encode(&hill, input, &output);
        // printf("encoded: <%s>\n", output);
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

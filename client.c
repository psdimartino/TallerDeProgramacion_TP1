#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common_socket.h"
#include "common_mod26.h"
#include "client_file.h"
#define BUFFER_SIZE 64
#define KEY_MAXLENGTH 64

int main(int argc, char *argv[]) {
    char *input;
    int *output, l;
    socket_t skt;
    file inputFile;
    if ( file_create(&inputFile, argv[3]) ) {
        fprintf(stderr, "file_create failed");
        return 1;
    }
    if ( socket_init(&skt) ) {
        fprintf(stderr, "socket_init failed");
        return 1;
    }
    if ( socket_connect(&skt, argv[2]/*service*/, argv[1]/*port*/) ) {
        fprintf(stderr, "socket_connect failed");
        return 1;
    }
    while (!file_isEmpty(&inputFile)) {
        if ( file_getLine(&inputFile, &input) ) {
            fprintf(stderr, "file_getLine failed");
            return 1;
        }
        if ( socket_send_string(&skt, input) ) {
            fprintf(stderr, "socket_send failed");
            socket_uninit(&skt);
            return 1;
        }
        if ( socket_read_int(&skt, &output, &l) ) {
            fprintf(stderr, "socket_send failed");
            socket_uninit(&skt);
            return 1;
        }
        printf("received bytes: %d, received ints/string: ", l);
        for (int i = 0; i < l; i ++) {
            printf("%d", (int)output[i]);
        }
        for (int i = 0; i < l; i ++) {
            printf("%c", mod26_getChar(output[i]));
        }
        printf("\n");
        free(input);
        free(output);
    }
    if ( socket_uninit(&skt) ) {
        fprintf(stderr, "socket_uninit failed");
        return 1;
    }
    if ( file_destroy(&inputFile) ) {
        fprintf(stderr, "file_destroy failed");
        return 1;
    }
    return 0;
}

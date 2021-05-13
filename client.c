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

#define MAX_LENGTH (16*16)-1

int main(int argc, char *argv[]) {
    char input[MAX_LENGTH] = {0};
    mod26 output[MAX_LENGTH] = {0};
    socket_t skt;
    file inputFile;
    file_init(&inputFile, argv[3]);
    socket_init(&skt);
    socket_connect(&skt, argv[2]/*service*/, argv[1]/*port*/);
    while (file_getLine(&inputFile, input)) {
        int l;
        socket_send(&skt, input, strlen(input));
        l = socket_read(&skt, (char *)&output);
        for (int i = 0; i < l; i ++) {
            printf("%c", output[i] + 'A');
        }
        printf("\n");
    }
    socket_uninit(&skt);
    file_uninit(&inputFile);
    return(EXIT_SUCCESS);
}

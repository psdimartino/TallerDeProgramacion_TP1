#include <string.h>

#include "client_client.h"

void client_init(client *this, const char *service,
                const char *port, const char *filename) {
    file_init(&this->input, filename);
    socket_init(&this->skt);
    socket_connect(&this->skt, service, port);
}

void client_read(client *this) {
    char input[MAX_LENGTH];
    mod26 output[MAX_LENGTH];
    while (file_getLine(&this->input, input)) {
        uint16_t l;
        socket_send(&this->skt, input, strlen(input));
        l = socket_read(&this->skt, (char *)&output);
        for (uint16_t i = 0; i < l; i ++) {
            printf("%c", mod26_getChar(output[i]));
        }
        printf("\n");
    }
}

void client_uninit(client *this) {
    socket_uninit(&this->skt);
    file_uninit(&this->input);
}

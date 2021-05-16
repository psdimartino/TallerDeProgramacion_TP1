#include "server_server.h"

void server_init(server *this, const char *port, const char *key) {
    socket_init(&this->skt);
    encoder_init(&this->hill, key);
    socket_bind(&this->skt, port);
    socket_listen(&this->skt);
    socket_accept(&this->skt);
}

void server_read(server *this) {
    char input[MAX_LENGTH];
    mod26 output[MAX_LENGTH];
     while (socket_read(&this->skt, input)) {
        uint16_t l;
        encoder_encode(&this->hill, input, output, &l);
        socket_send(&this->skt, (char *)output, l);
    }
}

void server_uninit(server *this) {
    encoder_uninit(&this->hill);
    socket_uninit(&this->skt);
}

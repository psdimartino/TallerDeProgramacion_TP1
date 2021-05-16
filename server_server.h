#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "common_socket.h"
#include "server_encoder.h"

#define MAX_LENGTH 65535

typedef struct server_t {
    encoder hill;
    socket_t skt;
} server;

void server_init(server *this, const char *port, const char *key);

void server_read(server *this);

void server_uninit(server *this);

#endif  // SERVER_SERVER_H_

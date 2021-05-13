#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "common_mod26.h"

typedef struct Socket{
    int sfd;
    struct addrinfo hints;
    struct sockaddr peer_addr;
} socket_t;

void socket_init(socket_t *this);

void socket_connect(socket_t *this, const char *service, const char *port);

void socket_send(socket_t *this, const char *data, int l);

int socket_read(socket_t *this, char *data);

void socket_uninit(socket_t *this);

void socket_bind(socket_t *this, const char *port);

void socket_accept(socket_t *this);

void socket_listen(socket_t *this);

#endif

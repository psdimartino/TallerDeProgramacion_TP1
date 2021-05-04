#define _POSIX_C_SOURCE 200809L
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#define BUF_SIZE 32

typedef struct Socket {
    int sfd;
    struct addrinfo hints;
    struct sockaddr peer_addr;
} socket_t;

int socket_init(socket_t *self ) {
    memset(self, 0, sizeof(socket_t));
    self->hints.ai_family = AF_INET;
    self->hints.ai_socktype = SOCK_STREAM;
    return 0;
}

int socket_connect(socket_t *self, const char *service, const char *port ) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(port, service, &self->hints, &result)) != 0) return 1;
    for ( self->sfd = 0, it = result; it != NULL; it = it->ai_next ) {
        self->sfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if (self->sfd != -1) {
            if ( connect(self->sfd, it->ai_addr, it->ai_addrlen) != -1 ) {
                freeaddrinfo(result);
                return 0;
            } else { close(self->sfd); }
        }
    }
    freeaddrinfo(result);
    return 1;
}

int socket_bind(socket_t *self, const char *port ) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(NULL, port, &self->hints, &result)) != 0) return 1;
    it = result;
    for ( self->sfd = 0; it != NULL; it = it->ai_next ) {
        self->sfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if ( self->sfd != -1 ) {
            if ( bind(self->sfd, it->ai_addr, it->ai_addrlen) == 0 ) {
                // self->isUp = true;
                freeaddrinfo(result);
                return 0;
            } else { close(self->sfd); }
        }
    }
    freeaddrinfo(result);
    return 1;
}

int socket_accept(socket_t *self) {
    struct sockaddr peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);
    int cfd;
    if ( (cfd = accept(self->sfd, &peer_addr, &peer_addr_len)) == -1 ) {
        return 1;
    }
    close(self->sfd);
    self->sfd = cfd;
    return 0;
}

int socket_listen(socket_t *self ) {
    if ( listen(self->sfd, 10) == -1 ) {
        return 1;
    }
    return 0;
}

int socket_uninit(socket_t *self ) {
    close(self->sfd);
    self->sfd = -1;
    return 0;
}


int socket_send_string(socket_t *self, const char *data) {
    int sent = 0, l = strlen(data) + 1;
    unsigned char size[2] = {l / 256, l % 256};  // Int to unsigned char
    // Send 2 bytes with string length
    while ((sent+=send(self->sfd, &size[sent], 2 - sent, MSG_NOSIGNAL)) < 2) {
    }
    // Send string
    sent = 0;
    while ((sent+=send(self->sfd, &data[sent], l - sent, MSG_NOSIGNAL)) < l) {
    }
    return 0;
}

int socket_read_string(socket_t *self, char **data) {
    int rec = 0, l;
    unsigned char size[2];
    // recive 2 bytes of string length
    while ((rec += recv(self->sfd, &size[rec], 2 - rec , 0) ) < 2) {
        if (rec == 0) {
            return 1;
        }
    }
    // recive string
    rec = 0;
    l = size[0] * 256 + size[1];  // Unisgned char to int;
    if ((*data = (char*) calloc(l + 1, sizeof(char))) == NULL) {
        return 1;
    }
    while ((rec += recv(self->sfd, &(*data)[rec], l - rec , 0)) < l) {
        if (rec == 0) {
            return 1;
        }
    }
    return 0;
}

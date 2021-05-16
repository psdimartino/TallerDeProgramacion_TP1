#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include "common_socket.h"
#include "client_file.h"

#define MAX_LENGTH 65535

typedef struct client_t {
    socket_t skt;
    file input;
} client;

void client_init(client *this, const char *service,
                const char *port, const char *filename);

void client_read(client *this);

void client_uninit(client *this);


#endif  // CLIENT_CLIENT_H_

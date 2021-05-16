#include <stdlib.h>

#include "server_server.h"

int main(int argc, char *argv[]) {
    server srvr;

    server_init(&srvr, argv[1], argv[2]);

    server_read(&srvr);

    server_uninit(&srvr);

    return(EXIT_SUCCESS);
}

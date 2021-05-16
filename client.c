#include <stdlib.h>

#include "client_client.h"

int main(int argc, char *argv[]) {
    client clnt;

    client_init(&clnt, argv[2], argv[1], argv[3]);

    client_read(&clnt);

    client_uninit(&clnt);

    return(EXIT_SUCCESS);
}

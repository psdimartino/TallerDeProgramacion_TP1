#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common_error.h"

void error_exit_errno(const char * msg, int _errno) {
    fprintf(stderr, "%s : %s\n", msg, strerror(errno));
    fprintf(stderr, "\x1b[31mEXIT_FAILURE \x1b[0m\n");
    exit(EXIT_FAILURE);
}

void error_exit_msg(const char * msg) {
    fprintf(stderr, "Error: %s\n", msg);
    fprintf(stderr, "\x1b[31mEXIT_FAILURE \x1b[0m\n");
    exit(EXIT_FAILURE);
}

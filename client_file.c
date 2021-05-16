#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "client_file.h"
#include "common_error.h"

#define MAX_LENGTH (16*16)-1

void file_init(file *this, const char *name) {
    if (strncmp(name, "-", 1) == 0) {
      this->file = stdin;
    } else {
        this->file = fopen(name, "r");
    }
    if (this->file == NULL) {
        error_exit_msg("Error while opening file");
    }
}

int file_getLine(file *this, char *output) {
    if (fgets(output, MAX_LENGTH, this->file) == NULL) {
        if (errno == 0) return 0;
        error_exit_msg("Error while reading line");
    }
    return 1;
}

void file_uninit(file *this) {
    if (this->file == stdin) return;
    if (fclose(this->file)) {
        error_exit_errno("While closing file", errno);
    }
}

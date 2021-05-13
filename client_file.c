#include "client_file.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "common_error.h"

#define MAX_LENGTH (16*16)-1

void file_init(file *this, char *name) {
    if (strncmp(name, "-", 1) == 0) {
      this->file = stdin;
    } else {
        this->file = fopen(name, "r");
    }
    if (this->file == NULL) {
        error_exit_msg("Error while opening file");
    }
}

// int isEmpty(file *this) {
//     return (feof(this->file) != 0);
// }

int file_getLine(file *this, char *output) {
    // do {
    if (fgets(output, MAX_LENGTH, this->file) == NULL) {
        if (errno == 0) return 0;
        error_exit_msg("Error while reading line");
    }
    // } while (strlen(output) == 1 && !isEmpty(this));
    return 1;
}

void file_uninit(file *this) {
    if (fclose(this->file)) {
        error_exit_errno("While closing file", errno);
    }
}

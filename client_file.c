#include "client_file.h"
#include <stdio.h>

int file_create(file *self, char *name) {
    if (name[0] == '-') {
        self->file = stdin;
    } else {
        self->file = fopen(name, "r");
    }
    if (self->file == NULL) {
        return 1;
    }
    return 0;
}

int file_getLine(file *self, char **output) {
    *output = NULL;
    int length = 0;
    size_t size = 0;
    if ((length = getline(output, &size, self->file)) == -1) {
        return 1;
    }
    (*output)[length-1] = '\n';
    return 0;
}

int file_isEmpty(file *self) {
    return (feof(self->file) != 0);
}

int file_destroy(file *self) {
    return fclose(self->file);
}

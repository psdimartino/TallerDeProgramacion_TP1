#ifndef CLIENT_FILE_H_
#define CLIENT_FILE_H_
#include <stdio.h>

typedef struct file_t {
    FILE *file;
} file;  

int file_create(file *self, char *name);

int file_getLine(file *self, char **output);

int file_isEmpty(file *self);

int file_destroy(file *self);

#endif  // CLIENT_FILE_H_
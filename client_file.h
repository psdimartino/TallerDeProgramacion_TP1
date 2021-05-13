#ifndef CLIENT_FILE_H_
#define CLIENT_FILE_H_
#include <stdio.h>

typedef struct file_t {
    FILE *file;
} file;  

void file_init(file *this, char *name);

int file_getLine(file *this, char *output);

void file_uninit(file *this);

#endif  // CLIENT_FILE_H_

#include "server_mod26.h"
#include <stdio.h>

mod26 mod26_create(int a) {
    return a % 26;
}

mod26 mod26_multiply(mod26 a, mod26 b) {
    return (a * b) % 26;
}

mod26 mod26_sum(mod26 a, mod26 b) {
    return (a + b) % 26;;
}


mod26 mod26_createFromChar(unsigned char c) {
    char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < 26; i++) {
        if (c == alphabet[i]) {
            return i;
        }
    }
    return -1;
}

unsigned char mod26_getChar(mod26 a) {
    char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphabet[a];
}

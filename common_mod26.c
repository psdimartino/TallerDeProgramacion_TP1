#include "common_mod26.h"
#include "common_error.h"

#include <stdio.h>

mod26 mod26_getChar(mod26 this) {
    return this + 'A';
}

mod26 mod26_multiply(mod26 a, mod26 b) {
    return (a * b) % 26;
}

mod26 mod26_sum(mod26 a, mod26 b) {
    return (a + b) % 26;
}

mod26 mod26_init(unsigned char c) {
    if ( c < 'A' || c > 'Z' ) {
        error_exit_msg("mod26 init failed. Bad value.");
    }
    return c - 'A';
}

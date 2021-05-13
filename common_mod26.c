#include "common_mod26.h"
#include "common_error.h"
#include <stdio.h>
// int toInt(mod26 a) {
//     return a - 'A';
// }

// mod26 toMod26(int i) {
//     return i + 'A';
// }

mod26 mod26_multiply(mod26 a, mod26 b) {
    // fprintf(stderr, "%u * %u = %u = %c * %c = %c\n",
    //         toInt(a), toInt(b), ((toInt(a) * toInt(b)) % 26),
    //          a, b, toMod26((toInt(a) * toInt(b)) % 26));
    return (a * b) % 26;
}

mod26 mod26_sum(mod26 a, mod26 b) {
    // fprintf(stderr, "%d + %d = %d = %c + %c = %c\n",
    //         toInt(a), toInt(b), ((toInt(a) + toInt(b)) % 26),
    //          a, b, toMod26((toInt(a) + toInt(b)) % 26));
    return (a + b) % 26;
}

mod26 mod26_init(unsigned char c) {
    if ( c < 'A' || c > 'Z' ) {
        fprintf(stderr, "In character <%c> ", c);
        error_exit_msg("mod26 init failed. Bad value.");
    }
    return c - 'A';
}

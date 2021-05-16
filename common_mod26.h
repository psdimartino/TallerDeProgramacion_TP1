#ifndef COMMON_MOD26_H_
#define COMMON_MOD26_H_

#include <stdint.h>

typedef uint8_t mod26;

mod26 mod26_init(unsigned char c);

mod26 mod26_multiply(mod26 a, mod26 b);

mod26 mod26_sum(mod26 a, mod26 b);

mod26 mod26_getChar(mod26 this);

#endif  // COMMON_MOD26_H_

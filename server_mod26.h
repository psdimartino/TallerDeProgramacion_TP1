#ifndef SERVER_MOD26_H_
#define SERVER_MOD26_H_

#include <stdlib.h>

typedef int mod26;

mod26 mod26_create(int a);

mod26 mod26_multiply(mod26 a, mod26 b);

mod26 mod26_createFromChar(unsigned char c);

mod26 mod26_sum(mod26 a, mod26 b);

unsigned char mod26_getChar(mod26 a);

#endif  // SERVER_MOD26_H_

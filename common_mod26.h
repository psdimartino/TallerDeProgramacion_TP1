#ifndef COMMON_MOD26_H_
#define COMMON_MOD26_H_

typedef unsigned char mod26;

mod26 mod26_init(unsigned char c);

mod26 mod26_multiply(mod26 a, mod26 b);

mod26 mod26_sum(mod26 a, mod26 b);

#endif  // COMMON_MOD26_H_

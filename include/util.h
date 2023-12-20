#include <stdint.h>

#define max(a, b) a < b ? b : a;
#define min(a, b) a < b ? a : b;

int8_t sign(double value);

uint64_t gcd(uint64_t f1, uint64_t f2);

uint64_t lcm(uint64_t f1, uint64_t f2);

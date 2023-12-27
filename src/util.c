#include <stdint.h>
#include "util.h"

int8_t sign(double value) {
    if (value > 0) {
        return 1;
    } else if (value < 0) {
        return -1;
    }
    return 0;
}

uint64_t gcd(uint64_t f1, uint64_t f2) {
    uint64_t a = max(f1, f2);
    uint64_t b = min(f1, f2);
    uint64_t r = a % b;
    uint64_t gcd = b;

    while (r != 0) {
        a = b;
        b = r;
        gcd = r;
        r = a % b;
        //printf("a =%lu b=%lu gcd=%lu r=%lu\n", a, b, gcd, r);
    }

    return gcd;
}

uint64_t lcm(uint64_t f1, uint64_t f2) {
    return (f1 * f2) / gcd(f1, f2);
}

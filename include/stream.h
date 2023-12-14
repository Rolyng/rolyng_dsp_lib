#pragma once

#include <stdint.h>

struct stream{
    double* samples;
    uint32_t size;
};

void freeStream(struct stream* stream);


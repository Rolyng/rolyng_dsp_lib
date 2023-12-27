#pragma once

#include <stdint.h>
#include "types.h"

struct stream {
    frequency sampleFreq;
    double* samples;
    uint32_t size;
};

void freeStream(struct stream* stream);

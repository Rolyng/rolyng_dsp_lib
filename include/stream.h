#pragma once

#include <complex.h>
#include <stdint.h>

struct stream {
    complex double sampleFreq;
    complex double* samples;
    uint32_t size;
};

void freeStream(struct stream* stream);

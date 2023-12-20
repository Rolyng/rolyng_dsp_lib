#include "stream.h"

struct dft_comp{
    double freq;
    double imag;
    double real;
    double phase;
};

struct dft_res{
    struct dft_comp* comp;
    uint32_t size;
};


struct dft_res dft(struct stream in, uint64_t sampleFreq, uint32_t numberOfPoints);

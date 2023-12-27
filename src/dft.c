#include "dft.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

struct dft_res dft(struct stream in, uint32_t N) {
    frequency baseFreq = (double)in.sampleFreq / N;
    struct dft_res res;
    res.size = N;
    res.comp = (struct dft_comp *)malloc(sizeof(struct dft_comp) * N);

    for (unsigned m = 0; m < N; m++) {
        complex double xm = 0;
        for (unsigned n = 0; n < N; n++) {
            xm += in.samples[n] * (cos(2 * M_PI * m * n / N) - I * sin(2 * M_PI * m * n / N));
        }
        struct dft_comp comp;
        comp.ampl = xm;
        comp.freq = baseFreq * m;
        res.comp[m] = comp;
        printf("Dft comp freq %f + %f i = %f + %f i\n", creal(comp.freq), cimag(comp.freq), creal(comp.ampl), cimag(comp.ampl));
    }

    return res;
}

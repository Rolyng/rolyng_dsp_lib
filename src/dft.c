#include "dft.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static complex double window_rectangle(complex double n, __attribute__((unused)) double N) {
    return n;
}

static complex double window_triangle(complex double n, double N) {
    if (creal(n) <= (N / 2)) {
        return n / (N / 2);
    }
    return 2 - n / (N / 2);
}

static complex double window_hanning(complex double n, double N) {
    return 0.5 - 0.5 * cos(2 * M_PI * n / N);
}

static complex double window_hamming(complex double n, double N) {
    return 0.54 - 0.46 * cos(2 * M_PI * n / N);
}

static windowFunc win_functions[DFT_WINDOW_LAST] = {
        [DFT_WINDOW_RECTANGLE] = &window_rectangle,
        [DFT_WINDOW_TRIANGLE] = &window_triangle,
        [DFT_WINDOW_HANNING] = &window_hanning,
        [DFT_WINDOW_HAMMING] = &window_hamming,
};

void apply_window(struct stream* in, enum dft_window win) {
    uint32_t N = in->size;
    for(unsigned i = 0; i < in->size; i++){
        in->samples[i] = win_functions[win](in->samples[i], N);
    }
}

struct dft_res dft(struct stream in, uint32_t N) {
    complex double baseFreq = (double)in.sampleFreq / N;
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
    }

    return res;
}

struct stream idft(struct dft_res dft_res) {
    complex double baseFreq = dft_res.comp[1].freq;
    struct stream res;
    uint32_t N = dft_res.size;
    res.size = N;
    res.sampleFreq = baseFreq * (N + 1);
    res.samples = (complex double *)malloc(sizeof(complex double) * N);

    for (unsigned m = 0; m < N; m++) {
        complex double xm = 0;
        for (unsigned n = 0; n < N; n++) {
            xm += dft_res.comp[n].ampl * (cos(2 * M_PI * m * n / N) + I * sin(2 * M_PI * m * n / N));
        }
        xm = xm / N;
        res.samples[m] = xm;
    }
    return res;
}

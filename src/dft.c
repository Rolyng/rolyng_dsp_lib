#include "dft.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static double window_rectangle(__attribute__((unused)) double n, __attribute__((unused)) double N) {
    return 1;
}

static double window_triangle(double n, double N) {
    if (n <= N / 2) {
        return n / (N / 2);
    }
    return 2 - n / (N / 2);
}

static double window_hanning(double n, double N) {
    return 0.5 - 0.5 * cos(2 * M_PI * n / N);
}

static double window_hamming(double n, double N) {
    return 0.54 - 0.46 * cos(2 * M_PI * n / N);
}

static windowFunc win_functions[DFT_WINDOW_LAST] = {
        &window_rectangle,
        &window_triangle,
        &window_hanning,
        &window_hamming,
};

struct dft_res dft(struct stream in, uint32_t N, enum dft_window win) {
    complex double baseFreq = (double)in.sampleFreq / N;
    struct dft_res res;
    res.size = N;
    res.comp = (struct dft_comp *)malloc(sizeof(struct dft_comp) * N);

    for (unsigned m = 0; m < N; m++) {
        complex double xm = 0;
        for (unsigned n = 0; n < N; n++) {
            xm += win_functions[win](n, N) * in.samples[n] *
                  (cos(2 * M_PI * m * n / N) - I * sin(2 * M_PI * m * n / N));
        }
        struct dft_comp comp;
        comp.ampl = xm;
        comp.freq = baseFreq * m;
        res.comp[m] = comp;
        //printf("Dft comp freq %f + %f i = %f + %f i\n", creal(comp.freq), cimag(comp.freq), creal(comp.ampl), cimag(comp.ampl));
    }

    return res;
}

struct stream idft(struct dft_res dft_res){
    complex double baseFreq = dft_res.comp[1].freq;
    struct stream res;
    uint32_t N = dft_res.size;
    res.size = N; 
    res.sampleFreq = baseFreq * (N+1);
    res.samples = (complex double *) malloc(sizeof(complex double) * N);

    for(unsigned m = 0; m < N; m++){
        complex double xm = 0;
        for(unsigned n = 0; n < N; n++){
            xm += dft_res.comp[n].ampl * (cos(2*M_PI*m*n/N) + I*sin(2*M_PI*m*n/N));
        }
        xm = xm/N;
        res.samples[m] = xm;
    }
    return res;
}

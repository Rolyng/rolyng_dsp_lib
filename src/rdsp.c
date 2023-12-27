#include "rdsp.h"
#include "signal.h"
#include "sample.h"
#include "stdio.h"
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include "dft.h"

int run(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    char *endptr = NULL;
    double sF = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        printf("Error char - %s", endptr);
        return 1;
    }
    double complex sampleFreq = sF;
    struct contSigComp sine = {.amplitude = 1, .freq = 1000, .sineWave.phase = 0, .type = COMP_SINE};
    struct contSigComp sine2 = {
            .amplitude = 0.5,
            .freq = 2000,
            .sineWave.phase = M_PI_4 * 3,
            .type = COMP_SINE,
    };
    struct contSig sig = {0};
    addComp(&sig, &sine);
    addComp(&sig, &sine2);
    struct stream res = gen_samplePeriod(&sig, sampleFreq);
    struct dft_res d = dft(res, res.size);
    for (uint64_t i = 0; i < res.size; i++) {
        printf("Sample %lu = %f\n", i, res.samples[i]);
    }
    for (uint64_t i = 0; i < res.size; i++) {
        printf("Dft comp freq %f + %f i = %f + %f i\n", creal(d.comp[i].freq), cimag(d.comp[i].freq),
                creal(d.comp[i].ampl), cimag(d.comp[i].ampl));
    }

    freeStream(&res);
    return 0;
}

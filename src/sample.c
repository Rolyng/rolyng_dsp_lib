#include "sample.h"
#include "stream.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

double calcComponent(struct contSigComp *comp, double time) {
    double res = 0;
    switch (comp->type) {
        case COMP_SINE: {
            res = sin((2.0 * M_PI * comp->freq * time) + comp->sineWave.phase);
            res *= comp->amplitude;
            break;
        };
        case COMP_COSINE: {
            res = cos((2 * M_PI * comp->freq * time) + comp->cosineWave.phase);
            res *= comp->amplitude;
            break;
        };
        case COMP_SQUARE: {
            res = sign(sin(2 * M_PI * comp->freq * time));
            res *= comp->amplitude;
            break;
        };
        case COMP_TRIANGLE: {
            res = 2 * (time * comp->freq - floor(time * comp->freq + 0.5));
            res *= comp->amplitude;
            break;
        };

        case COMP_SAWTOOTH: {
            res = 2 * (time * comp->freq - floor(time * comp->freq + 0.5)) - 1;
            res *= comp->amplitude;
        };
    }
    return res;
}

double gen_sample(struct contSig *sig, double time) {
    double res = 0;
    struct contSigComp *comp = sig->frComps;
    while (comp != NULL) {
        res += calcComponent(comp, time);
        comp = comp->next;
    }
    return res;
}

/* When sampling there will be some number of samples until they start repeating
so this function does that. it samples for one such period. */
struct stream gen_samplePeriod(struct contSig *sig, complex double sampleFreq) {
    struct stream res;
    if (sampleFreq == 0 || sig->freq == 0) {
        res.size = 1;
    //trunc(NAN) is not equal to NAN. not sure if it's well-defined behavior or not
    } else if(trunc(sampleFreq) == sampleFreq && trunc(sig->freq) == sig->freq){
        //is this right???
        res.size = sampleFreq / gcd(sampleFreq, sig->freq);
    }else{
        return gen_sampleDuration(sig, sampleFreq, 1.0);
    }
    res.samples = (complex double *)malloc(sizeof(complex double) * res.size);
    double samplePeriod = 1.0 / sampleFreq;

    for (uint64_t i = 0; i < res.size; i++) {
        res.samples[i] = gen_sample(sig, samplePeriod * i);
    }
    res.sampleFreq = sampleFreq;

    return res;
}

struct stream gen_sampleDuration(struct contSig *sig, complex double sampleFreq, double duration) {
    struct stream res;
    double samplePeriod;
    if (duration <= 0) {
        fprintf(stderr, "gen_sampleDuration duration <= 0");
        res.size = 0;
        res.samples = NULL;
        return res;
    }
    if (sampleFreq == 0 || sig->freq == 0) {
        res.size = 1;
    } else {
        samplePeriod = 1.0 / sampleFreq;
        res.size = duration / samplePeriod;
    }
    res.samples = (complex double *)malloc(sizeof(complex double) * res.size);

    for (uint64_t i = 0; i < res.size; i++) {
        res.samples[i] = gen_sample(sig, samplePeriod * i);
    }
    res.sampleFreq = sampleFreq;

    return res;
}


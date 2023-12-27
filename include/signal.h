#pragma once

#include "stream.h"
#include <complex.h>
#include <stdint.h>

enum contSigCompType {
    COMP_SINE,
    COMP_COSINE,
    COMP_SQUARE,
    COMP_TRIANGLE,
    COMP_SAWTOOTH,
};

struct contSigComp {
    double amplitude;
    complex double freq;
    union {
        struct {
            double phase;
        } sineWave, cosineWave;
        struct {
            double dutyCycle;
        } squareWave;
        struct {
        } triangleWave;
        struct {
        } sawtoothWave;
    };
    enum contSigCompType type;
    struct contSigComp *next;
};

struct contSig {
    struct contSigComp *frComps;
    //TODO do it like Maybe from Haskell
    complex double freq;
};

void addComp(struct contSig *sig, struct contSigComp *comp);

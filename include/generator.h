#pragma once

#include "stream.h"
struct generator{
    double (*genFunc)(double time);
    double period;
};


double gen_getSample(struct generator gen, double time);
struct stream gen_getStream(struct generator gen, double sampleFreq);

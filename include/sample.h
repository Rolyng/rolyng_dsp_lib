#pragma once

#include <complex.h>
#include "stream.h"
#include "signal.h"

double gen_sample(struct contSig *sig, double time);

struct stream gen_samplePeriod(struct contSig *sig, complex double sampleFreq);

struct stream gen_sampleDuration(struct contSig *sig, complex double sampleFreq, double duration);

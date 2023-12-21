#pragma once

#include "types.h"
#include "stream.h"
#include "signal.h"

double gen_sample(struct contSig *sig, double time);

struct stream gen_samplePeriod(struct contSig *sig, frequency sampleFreq);

struct stream gen_sampleDuration(struct contSig *sig, frequency sampleFreq, double duration);

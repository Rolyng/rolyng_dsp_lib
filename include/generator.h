#pragma once

#include "stream.h"
#include <stdint.h>

enum compType {
	COMP_SINE,
	COMP_COSINE,
	COMP_SQUARE,
	COMP_TRIANGLE,
	COMP_SAWTOOTH,
};

struct signalComp {
	double amplitude;
    uint64_t freq;
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
	enum compType type;
	struct signalComp *next;
};

struct signal {
	struct signalComp *frComps;
	uint64_t freq;
};

void gen_addComp(struct signal *sig, struct signalComp *comp);

double gen_sample(struct signal *sig, double time);

struct stream gen_samplePeriod(struct signal *sig, uint64_t sampleFreq);

struct stream gen_sampleDuration(struct signal *sig, uint64_t sampleFreq, double duration);

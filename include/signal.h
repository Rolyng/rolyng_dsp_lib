#pragma once

#include "stream.h"
#include <stdint.h>
#include "types.h"

enum contSigCompType {
	COMP_SINE,
	COMP_COSINE,
	COMP_SQUARE,
	COMP_TRIANGLE,
	COMP_SAWTOOTH,
};

struct contSigComp {
	double amplitude;
    frequency freq;
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
	frequency freq;
};

void addComp(struct contSig *sig, struct contSigComp *comp);


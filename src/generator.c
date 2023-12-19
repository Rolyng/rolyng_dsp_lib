#include "generator.h"
#include "stream.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define max(a, b) a < b ? b : a;
#define min(a, b) a < b ? a : b;

static int8_t sign(double value) {
	if (value > 0) {
		return 1;
	} else if (value < 0) {
		return -1;
	}
	return 0;
}

static uint64_t gcd(uint64_t f1, uint64_t f2) {
	uint64_t a = max(f1, f2);
	uint64_t b = min(f1, f2);
	uint64_t r = a % b;
	uint64_t gcd = b;

	while (r != 0) {
		a = b;
		b = r;
		gcd = r;
		r = a % b;
		//printf("a =%lu b=%lu gcd=%lu r=%lu\n", a, b, gcd, r);
	}

	return gcd;
}

static uint64_t lcm(uint64_t f1, uint64_t f2) {
	return (f1 * f2) / gcd(f1, f2);
}

double calcComponent(struct signalComp *comp, double time) {
	double res = 0;
	switch (comp->type) {
		case COMP_SINE: {
			res = sin((2.0 * M_PI * comp->sineWave.freq * time) + comp->sineWave.phase);
			res *= comp->amplitude;
			break;
		};
		case COMP_COSINE: {
			res = cos((2 * M_PI * comp->cosineWave.freq * time) + comp->cosineWave.phase);
			res *= comp->amplitude;
			break;
		};
		case COMP_SQUARE: {
			res = sign(sin(2 * M_PI * comp->squareWave.freq * time));
			res *= comp->amplitude;
			break;
		};
		case COMP_TRIANGLE: {
			res = 2 * (time * comp->triangleWave.freq - floor(time * comp->triangleWave.freq + 0.5));
			res *= comp->amplitude;
			break;
		};

		case COMP_SAWTOOTH: {
			res = 2 * (time * comp->triangleWave.freq - floor(time * comp->triangleWave.freq + 0.5)) - 1;
			res *= comp->amplitude;
		};
	}
	return res;
}

double gen_getSample(struct signal *sig, double time) {
	double res = 0;
	struct signalComp *comp = sig->frComps;
	while (comp != NULL) {
		res += calcComponent(comp, time);
		comp = comp->next;
	}
	return res;
}

struct stream gen_samplePeriod(struct signal *sig, uint64_t sampleFreq) {
	struct stream res;
	if (sampleFreq == 0 || sig->freq == 0) {
		res.size = 1;
	} else {
		res.size = lcm(sampleFreq, sig->freq);
	}
	res.samples = (double *)malloc(sizeof(double) * res.size);
	double samplePeriod = 1.0 / sampleFreq;

	for (uint64_t i = 0; i < res.size; i++) {
		res.samples[i] = gen_getSample(sig, samplePeriod * i);
	}

	return res;
}

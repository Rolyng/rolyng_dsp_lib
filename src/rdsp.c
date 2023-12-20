#include "rdsp.h"
#include "generator.h"
#include "stdio.h"
#include <math.h>
#include <stdlib.h>

int run(int argc, char *argv[]) {
	if (argc < 4) {
		return 1;
	}
	char *endptr = NULL;
	double sampleFreq = strtod(argv[1], &endptr);
	if (*endptr != '\0') {
		printf("Error char - %s", endptr);
		return 1;
	}
	double end = strtod(argv[2], &endptr);
	if (*endptr != '\0') {
		printf("Error char - %s", endptr);
		return 1;
	}
	double phase = strtod(argv[3], &endptr);
	if (*endptr != '\0') {
		printf("Error char - %s", endptr);
		return 1;
	}
	struct signalComp sine = {.amplitude = 1,
			.freq = 1000,
			.sineWave.phase = 0,
			.type = COMP_SINE,
			.next = NULL};
	struct signalComp cosine = {.amplitude = 0.5, .freq = 2000, .sineWave.phase = M_PI_4*3, .type = COMP_SINE,};
	struct signal sig = {0};
	gen_addComp(&sig, &sine);
	gen_addComp(&sig, &cosine);
	struct stream res = gen_samplePeriod(&sig, sampleFreq);
	for (uint64_t i = 0; i < res.size; i++) {
		printf("Sample %lu = %f\n", i, res.samples[i]);
	}

    freeStream(&res);
	return 0;
}

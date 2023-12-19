#include "rdsp.h"
#include "generator.h"
#include "stdio.h"
#include <stdlib.h>


int run(int argc, char* argv[]) {
    if(argc < 3){
        return 1;
    }
    char *endptr = NULL;
    double sampleFreq = strtod(argv[1], &endptr);
    if(*endptr != '\0'){
        printf("Error char - %s", endptr);
        return 1;
    }
    double end = strtod(argv[2], &endptr);
    if(*endptr != '\0'){
        printf("Error char - %s", endptr);
        return 1;
    }
    struct signalComp sine = {.amplitude=2, .sineWave.freq=255, .sineWave.phase=0.2, .type=COMP_SINE, .next=NULL};
    struct signal sig = {.frComps=&sine, .freq=sine.sineWave.freq};
    struct stream res = gen_samplePeriod(&sig, sampleFreq);
    for(uint64_t i = 0; i < res.size; i++){
        printf("Sample %lu = %f\n", i, res.samples[i]);
    }
    
    return 0;
}


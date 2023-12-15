#include "rdsp.h"
#include "generator.h"
#include "stdio.h"
#include <stdlib.h>


int run(int argc, char* argv[]) {
    if(argc < 3){
        return 1;
    }
    char *endptr = NULL;
    double inc = strtod(argv[1], &endptr);
    inc = 1.0/inc;
    if(*endptr != '\0'){
        printf("Error char - %s", endptr);
        return 1;
    }
    double end = strtod(argv[2], &endptr);
    if(*endptr != '\0'){
        printf("Error char - %s", endptr);
        return 1;
    }
    struct signalComp sine = {.amplitude=2, .sineWave.freq=13, .sineWave.phase=0.2, .type=COMP_SINE, .next=NULL};
    struct signal sig = {.frComps=&sine};
    for(double d = 0.0; d < 1.0; d += inc){
        printf("d = %.4f, comp = %f\n", d, gen_getSample(&sig, d));
    }
    return 0;
}


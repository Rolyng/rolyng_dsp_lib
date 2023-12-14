#include "rdsp.h"
#include "generator.h"
#include "stdio.h"

static double aboba(double a){
    return a*1.5;
}

int run(int argc, char* argv[]) {
    struct generator gen = {.genFunc=&aboba, .period=2};
    printf("Jopa = %f", gen_getSample(gen, 0.5));
    return 0;
}


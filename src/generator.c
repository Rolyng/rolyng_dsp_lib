#include "generator.h"
#include "stream.h"

double gen_getSample(struct generator gen, double time){
    return gen.genFunc(time);
}
struct stream gen_getStream(struct generator gen, double sampleFreq){
    struct stream result = {};
    return result;
}

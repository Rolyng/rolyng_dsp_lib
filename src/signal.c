#include "signal.h"
#include "stream.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void addComp(struct contSig *sig, struct contSigComp *comp) {
    comp->next = sig->frComps;
    sig->frComps = comp;
    sig->freq = sig->freq ? gcd(sig->freq, comp->freq) : comp->freq;
}

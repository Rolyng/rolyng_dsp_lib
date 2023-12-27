#include "signal.h"
#include "stream.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void addComp(struct contSig *sig, struct contSigComp *comp) {
    comp->next = sig->frComps;
    sig->frComps = comp;
    if (sig->freq == NAN) {
        return;
    }
    if (!sig->freq) {
        sig->freq = comp->freq;
        return;
    }
    //trunc(NAN) is not equal to NAN but to be sure i added check before
    if (trunc(comp->freq) == comp->freq && trunc(sig->freq) == sig->freq) {
        sig->freq = gcd(sig->freq, comp->freq);
    } else {
        //impossible to do in general case so just dont bother and "put" an error
        sig->freq = NAN;
    }
}

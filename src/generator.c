#include "generator.h"
#include "stream.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int8_t sign(double value) {
  if (value > 0) {
    return 1;
  } else if (value < 0) {
    return -1;
  }
  return 0;
}

double calcComponent(struct signalComp *comp, double time) {
  double res = 0;
  switch (comp->type) {
  case COMP_DC: {
    res += comp->amplitude;
    break;
  };
  case COMP_SINE: {
    res = sin((2.0 * M_PI * comp->sineWave.freq * time) +
              comp->sineWave.phase);
    res *= comp->amplitude;
    break;
  };
  case COMP_COSINE: {
    res = cos((2 * M_PI * comp->cosineWave.freq * time) +
              comp->cosineWave.phase);
    res *= comp->amplitude;
    break;
  };
  case COMP_SQUARE: {
    res = sign(sin(2 * M_PI * comp->squareWave.freq * time));
    res *= comp->amplitude;
    break;
  };
  case COMP_TRIANGLE: {
    res = 2 * (time * comp->triangleWave.freq -
               floor(time * comp->triangleWave.freq + 0.5));
    res *= comp->amplitude;
    break;
  };

  case COMP_SAWTOOTH: {
    res = 2 * (time * comp->triangleWave.freq -
               floor(time * comp->triangleWave.freq + 0.5)) -
          1;
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
struct stream gen_getStream(struct signal *sig, double sampleFreq) {
  struct stream result = {};
  return result;
}

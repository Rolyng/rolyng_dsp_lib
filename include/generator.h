#pragma once

#include "stream.h"
#include <stdint.h>

enum compType{
    COMP_SINE,
    COMP_COSINE,
    COMP_SQUARE,
    COMP_TRIANGLE,
    COMP_SAWTOOTH,
};

struct signalComp {
  double amplitude;
  union {
    struct {
      uint64_t freq;
      double phase;
    } sineWave, cosineWave;
    struct {
      uint64_t freq;
      double dutyCycle;
    } squareWave;
    struct {
      uint64_t freq;
    } triangleWave;
    struct {
        uint64_t freq;
    } sawtoothWave;
  };
  enum compType type;
  struct signalComp * next;
};

struct signal {
  struct signalComp *frComps;
  uint64_t freq;
};

void gen_addComp(struct signal *sig, struct signalComp *comp);

double gen_getSample(struct signal *sig, double time);

struct stream gen_samplePeriod(struct signal *sig, uint64_t sampleFreq);

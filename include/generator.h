#pragma once

#include "stream.h"

enum compType{
    COMP_DC,
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
      double freq;
      double phase;
    } sineWave, cosineWave;
    struct {
      double freq;
      double dutyCycle;
    } squareWave;
    struct {
      double freq;
    } triangleWave;
    struct {
        double freq;
    } sawtoothWave;
  };
  enum compType type;
  struct signalComp * next;
};

struct signal {
  struct signalComp *frComps;
};


double gen_getSample(struct signal *sig, double time);

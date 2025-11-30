#pragma once

#include "AudioBuffer.h"

void applyFIR(const AudioBuffer& in,
              AudioBuffer& out,
              const float *h,
              size_t taps);
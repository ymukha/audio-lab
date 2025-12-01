#pragma once

#include "qtypes.h"
#include "AudioBuffer.h"

void applyFIR(const AudioBuffer<q15_t>& in,
              AudioBuffer<q15_t>& out,
              const q15_t *h,
              size_t taps);
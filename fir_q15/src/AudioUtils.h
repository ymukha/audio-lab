#pragma once

#define _USE_MATH_DEFINES

#include "qtypes.h"
#include "AudioBuffer.h"


AudioBuffer<float> makeSine(float frequency,
                     float amplitude,
                     float durationSeconds,
                     size_t sampleRate,
                     size_t channels);

AudioBuffer<q15_t> bufferFromFloat(const AudioBuffer<float>& buffer);
AudioBuffer<float> bufferToFloat(const AudioBuffer<q15_t>& buffer);

q15_t float_to_q15(float value);
float q15_to_float(q15_t value);
q15_t q15_saturate(q31_t value);
q15_t q15_add(q15_t a, q15_t b);
q15_t q15_sub(q15_t a, q15_t b);
q15_t q15_mul(q15_t a, q15_t b);
q31_t q15_mac(q31_t acc, q15_t a, q15_t b);
q15_t q15_from_acc(q31_t acc);
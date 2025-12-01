#include "AudioUtils.h"

#include <cmath>


AudioBuffer<float> makeSine(float frequency,
                     float amplitude,
                     float durationSeconds,
                     size_t sampleRate,
                     size_t channels)
{
    const float phase{0.0f};
    const float dT{1.0f / sampleRate};
    const float twoPiF{2.0f * float(M_PI) * frequency};

    size_t frames = static_cast<size_t>(durationSeconds * static_cast<double>(sampleRate));

    AudioBuffer<float> buffer { sampleRate, channels, frames };

    buffer.data.resize(frames * channels);

    for (size_t n = 0; n < frames; ++n)
    {
        const float sample{ amplitude * std::sin(twoPiF * n * dT)};

        for(size_t channel = 0; channel < channels; ++channel)
            buffer.data[n * channels + channel] = sample;
    }

    return buffer;
}

AudioBuffer<q15_t> bufferFromFloat(const AudioBuffer<float>& buffer)
{
    AudioBuffer<q15_t> result;

    result.channels = buffer.channels;
    result.frameCount = buffer.frameCount;
    result.sampleRate = buffer.sampleRate;
    result.data.resize(buffer.data.size());

    for (size_t idx = 0; idx < buffer.data.size(); ++idx)
        result.data[idx] = float_to_q15(buffer.data[idx]);

    return result;
}

AudioBuffer<float> bufferToFloat(const AudioBuffer<q15_t>& buffer)
{
    AudioBuffer<float> result;

    result.channels = buffer.channels;
    result.frameCount = buffer.frameCount;
    result.sampleRate = buffer.sampleRate;
    result.data.resize(buffer.data.size());

    for (size_t idx = 0; idx < buffer.data.size(); ++idx)
        result.data[idx] = q15_to_float(buffer.data[idx]);

    return result;
}

q15_t float_to_q15(float value)
{
    if (value >= 1.f)
        value = 0.999969482421875f;    
    else if (value < -1.f)
        value = -1.f;
    
    value *= 32768.f; // * 2^15

    q31_t ret = static_cast<q31_t>(std::lrintf(value));

    return q15_saturate(ret);
}

float q15_to_float(q15_t value)
{
    return static_cast<float>(value) / 32768.f; // / 2^15
}

q15_t q15_saturate(q31_t value)
{
    if (value > 32767)
        value = 32767;
    else if (value < -32768)
        value = -32768;

    return static_cast<q15_t>(value);
}

q15_t q15_add(q15_t a, q15_t b)
{
    q31_t result = static_cast<q31_t>(a) + static_cast<q31_t>(b);

    return q15_saturate(result);
}

q15_t q15_sub(q15_t a, q15_t b)
{
    q31_t result = static_cast<q31_t>(a) - static_cast<q31_t>(b);

    return q15_saturate(result);
}

q15_t q15_mul(q15_t a, q15_t b)
{
    q31_t result = static_cast<q31_t>(a) * static_cast<q31_t>(b); // Q15 * Q15 -> Q31

    if (result >= 0)
        result += 1 << 14; // Round to the nearest pos
    else
        result -= 1 << 14; // Round to the nearest neg

    result >>= 15; // Q31 -> Q15

    return q15_saturate(result);
}

q31_t q15_mac(q31_t acc, q15_t a, q15_t b)
{
    q31_t mul = static_cast<q31_t>(a) * static_cast<q31_t>(b); // Q15 * Q15 -> Q30

    return acc + mul; // Q30 + Q30
}

q15_t q15_from_acc(q31_t acc)
{
    if (acc >= 0)
        acc += (1 << 14); // Round to the nearest pos
    else
        acc -= (1 << 14); // Round to the nearest neg

    return q15_saturate(acc >> 15); // Q30 -> Q15
}
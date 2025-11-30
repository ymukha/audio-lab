#include "AudioUtils.h"

#define _USE_MATH_DEFINES

#include "AudioBuffer.h"

#include <cmath>

AudioBuffer makeSine(float frequency,
                     float amplitude,
                     float durationSeconds,
                     size_t sampleRate,
                     size_t channels)
{
    const float phase{0.0f};
    const float dT{1.0f / sampleRate};
    const float twoPiF{2.0f * float(M_PI) * frequency};

    size_t frames = static_cast<size_t>(durationSeconds * static_cast<double>(sampleRate));

    AudioBuffer buffer { sampleRate, channels, frames };

    buffer.data.resize(frames * channels);

    for (size_t n = 0; n < frames; ++n)
    {
        const float sample{ amplitude * std::sin(twoPiF * n * dT)};

        for(size_t channel = 0; channel < channels; ++channel)
            buffer.data[n * channels + channel] = sample;
    }

    return buffer;
}
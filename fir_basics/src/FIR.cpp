#include "FIR.h"

void applyFIR(const AudioBuffer& in,
              AudioBuffer& out,
              const float *h,
              size_t taps)
{
    if (in.channels != out.channels
        || in.sampleRate != out.sampleRate)
        return;

    out.data.clear();
    out.data.resize(in.data.size());
    
    const size_t channels { in.channels };
    const size_t frames = in.data.size() / in.channels;

    for (size_t channel = 0; channel < channels; ++channel)
    {
        for (size_t sample = 0; sample < frames; ++sample)
        {
            float acc{ 0.0f };

            for (size_t tap = 0; tap < taps; ++tap)
            {
                if (tap > sample)
                    continue;
                
                acc += h[tap] * in.data[channel + (sample - tap) * channels];
            }

            out.data[channel + sample * channels] = acc;
        }
    }
}
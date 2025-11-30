#include "FIR.h"

void applyFIR(const AudioBuffer& in,
              AudioBuffer& out,
              const float *h,
              size_t taps)
{
    if (taps == 0
        || h == nullptr)
        return;

    out.channels = in.channels;
    out.sampleRate = in.sampleRate;
    out.frameCount = in.frameCount;    

    out.data.clear();
    out.data.assign(in.data.size(), 0.0f);
    
    const size_t channels { in.channels };
    const size_t frames = in.frameCount;

    for (size_t channel = 0; channel < channels; ++channel)
    {
        for (size_t frame = 0; frame < frames; ++frame)
        {
            float acc{ 0.0f };

            for (size_t tap = 0; tap < taps; ++tap)
            {
                if (tap > frame)
                    continue;
                
                acc += h[tap] * in.data[channel + (frame - tap) * channels];
            }

            out.data[channel + frame * channels] = acc;
        }
    }
}
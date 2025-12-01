#include "FIR.h"

#include "AudioUtils.h"

void applyFIR(const AudioBuffer<q15_t>& in,
              AudioBuffer<q15_t>& out,
              const q15_t *h,
              size_t taps)
{
    if (taps == 0
        || h == nullptr)
        return;

    out.channels = in.channels;
    out.sampleRate = in.sampleRate;
    out.frameCount = in.frameCount;    

    out.data.clear();
    out.data.assign(in.data.size(), 0);
    
    const size_t channels{ in.channels };
    const size_t frames{ in.frameCount };

    for (size_t channel = 0; channel < channels; ++channel)
    {
        for (size_t frame = 0; frame < frames; ++frame)
        {
            q31_t acc{ 0 };

            const size_t maxTaps{ taps < frame + 1 ? taps : (frame + 1)};
            for (size_t tap = 0; tap < maxTaps; ++tap)
                acc = q15_mac(acc, h[tap], in.data[channel + (frame - tap) * channels]);

            out.data[channel + frame * channels] = q15_from_acc(acc);
        }
    }
}
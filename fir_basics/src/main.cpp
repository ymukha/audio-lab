
#include "AudioBuffer.h"
#include "AudioUtils.h"
#include "FIR.h"

#include <vector>
#include <iostream>


int main(int argc, char* argv[])
{
    const size_t sampleRate{48000};
    const float duration{0.01f}; // 10ms
    const size_t channels{2};
    const float amplitude{1.0f};

    // Sine input buffer
    auto input = makeSine(1000.0f, amplitude, duration, sampleRate, channels);

    // Prepare out buffer for FIR
    AudioBuffer output{input.sampleRate, input.channels, input.FrameSize};

    // FIR moving avg (5 taps)
    const size_t taps{ 5 };
    std::vector<float> h(taps, 1.0f/ taps);

    // Run FIR
    applyFIR(input, output, h.data(), h.size());

    // Print some in vs out
    constexpr size_t SamplesToPrint{ 16 };
    const size_t TotalSamplesToPrint{ SamplesToPrint * input.channels };
    for (std::size_t i = 0; i < TotalSamplesToPrint; ++i)
    {
        std::cout << i << ": in="  << input.data[i]
                  << "  out=" << output.data[i] << '\n';
    }

    return 0;
}
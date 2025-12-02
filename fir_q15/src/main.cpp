
#include "AudioBuffer.h"
#include "AudioUtils.h"
#include "FIR.h"
#include "ErrorStats.h"

#include <vector>
#include <iostream>
#include <exception>


int main(int argc, char* argv[]) try
{
    const size_t sampleRate{48000};
    const float duration{0.01f}; // 10ms
    const size_t channels{2};
    const float amplitude{1.0f};

    // Sine input buffer
    auto input = makeSine(1000.0f, amplitude, duration, sampleRate, channels);
    auto inputQ15 = bufferFromFloat(input);

    // Prepare out buffer for FIR
    AudioBuffer<q15_t> outputQ15{inputQ15.sampleRate, inputQ15.channels, inputQ15.frameCount};
    AudioBuffer<float> outputFloat{input.sampleRate, input.channels, input.frameCount};

    // FIR moving avg (5 taps)
    const size_t taps{ 5 };
    std::vector<q15_t> hQ15(taps, float_to_q15(1.0f/ taps));
    std::vector<float> hFloat(taps, 1.0f/ taps);

    // Run FIR
    applyFIR(inputQ15, outputQ15, hQ15.data(), hQ15.size());
    applyFIR(input, outputFloat, hFloat.data(), hFloat.size());

    auto output = bufferToFloat(outputQ15);

    auto stats = computeErrorStats(outputFloat, output);

    std::cout << "Error stats:" << std::endl;
    std::cout << "\tMSE       : " << stats.mse << std::endl;
    std::cout << "\tRMSE      : " << stats.rmse << std::endl;
    std::cout << "\tMax |err| : " << stats.maxAbsErr << std::endl;
    std::cout << "\tSNR, dB   : " << stats.snr << std::endl;

#if 0
    // Print some in vs out
    constexpr size_t SamplesToPrint{ 16 };
    const size_t TotalSamplesToPrint{ SamplesToPrint * inputQ15.channels };
    for (std::size_t i = 0; i < TotalSamplesToPrint; ++i)
    {
        std::cout << i << ": in="  << input.data[i]
                  << "  out=" << output.data[i] << '\n';
    }
#endif

    return 0;
}
catch(const std::exception& e)
{
    std::cout << e.what();
    return 0;
}
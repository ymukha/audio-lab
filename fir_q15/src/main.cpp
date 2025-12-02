
#include "AudioBuffer.h"
#include "AudioUtils.h"
#include "FIR.h"
#include "ErrorStats.h"

#include <vector>
#include <string>
#include <iostream>
#include <exception>

void makeTest(const AudioBuffer<float>& input, size_t taps, const std::string& testName)
{
    auto inputQ15 = bufferFromFloat(input);

    // Prepare out buffer for FIR
    AudioBuffer<q15_t> outputQ15{inputQ15.sampleRate, inputQ15.channels, inputQ15.frameCount};
    AudioBuffer<float> outputFloat{input.sampleRate, input.channels, input.frameCount};

    // FIR moving avg
    std::vector<q15_t> hQ15(taps, float_to_q15(1.0f/ taps));
    std::vector<float> hFloat(taps, 1.0f/ taps);

    // Run FIR
    applyFIR(inputQ15, outputQ15, hQ15.data(), hQ15.size());
    applyFIR(input, outputFloat, hFloat.data(), hFloat.size());

    auto output = bufferToFloat(outputQ15);

    auto stats = computeErrorStats(outputFloat, output);

    std::cout << "Test: " << testName << std::endl;
    std::cout << "\tError stats:" << std::endl;
    std::cout << "\t\tMSE       : " << stats.mse << std::endl;
    std::cout << "\t\tRMSE      : " << stats.rmse << std::endl;
    std::cout << "\t\tMax |err| : " << stats.maxAbsErr << std::endl;
    std::cout << "\t\tSNR, dB   : " << stats.snr << std::endl << std::endl;
}


int main(int argc, char* argv[]) try
{
    const size_t sampleRate{48000};
    const float duration{0.01f}; // 10ms
    const size_t channels{2};
    const float amplitude{1.0f};


    makeTest(makeSine(1000.0f, amplitude, duration, sampleRate, channels),
             5, "Sine (1kHz, amplitude = 1)");
    makeTest(makeSine(1000.0f, 0.9f, duration, sampleRate, channels),
             5, "Sine (1kHz, amplitude = 0.9)");
    makeTest(makeSine(1000.0f, 0.5f, duration, sampleRate, channels),
             5, "Sine (1kHz, amplitude = 0.5)");

    makeTest(makeDualSine(1000.0f, 3000.0f, amplitude, duration, sampleRate, channels),
             5, "Sine (1kHz + 3kHz)");

    std::vector<size_t> taps{ 5, 16, 64, 128, 512, 1024 };
    for (auto t : taps)
        makeTest(makeWhiteNoise(amplitude, duration, sampleRate, channels),
                 t, "White noise (taps = " + std::to_string(t) + ")");
    
    auto hfreq = sampleRate / 2.66f;
    makeTest(makeSine(hfreq, amplitude, duration, sampleRate, channels),
             5, "High-frequency Sine (" +std::to_string(hfreq) + "kHz)");

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
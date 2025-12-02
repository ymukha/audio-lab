#pragma once

#include "AudioBuffer.h"

struct ErrorStats
{
    double mse{0};
    double rmse{0};
    double maxAbsErr{0};
    double snr{0};
};

ErrorStats computeErrorStats(const AudioBuffer<float>& ref,
                             const AudioBuffer<float>& test);
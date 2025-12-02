#include "ErrorStats.h"

#include <stdexcept>
#include <cmath>
#include <limits>


ErrorStats computeErrorStats(const AudioBuffer<float>& ref,
                             const AudioBuffer<float>& test)
{
    if (ref.channels != test.channels
        || ref.sampleRate != test.sampleRate
        || ref.frameCount != test.frameCount
        || ref.data.size() != test.data.size())
        throw std::runtime_error("Buffer mismatch");

    const auto N = ref.data.size();
    if (!N)
        return {};

    double maxAbsErr{0};
    long double sumSqErr{0};
    long double sumSqRef{0};

    for (size_t i = 0; i < N; ++i)
    {
        const long double err = ref.data[i] - test.data[i]; // error

        const auto absErr = std::fabs(static_cast<double>(err));
        if (absErr > maxAbsErr)
            maxAbsErr = absErr;

        sumSqErr += err * err;
        sumSqRef += ref.data[i] * ref.data[i];
    }

    ErrorStats result;

    result.mse = sumSqErr / static_cast<long double>(N);
    result.rmse = std::sqrt(result.mse);
    result.maxAbsErr = maxAbsErr;

    if (sumSqRef > 0 && result.mse > 0)
    {
        const long double snr = sumSqRef / sumSqErr;
        result.snr = 10. * std::log10(static_cast<double>(snr));
    }
    else
    {
        result.snr = std::numeric_limits<double>::infinity();
    }

    return result;
}
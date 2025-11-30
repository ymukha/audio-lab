#pragma once

#include <vector>

struct AudioBuffer
{
    size_t sampleRate;
    size_t channels;
    size_t FrameSize;
    std::vector<float> data;
};
#pragma once

#include <vector>

struct AudioBuffer
{
    size_t sampleRate{ 48000 };
    size_t channels{ 2 };
    size_t frameCount{ 1 };
    std::vector<float> data;

    AudioBuffer() = default;
    
    AudioBuffer(size_t sr, size_t ch, size_t frames)
        : sampleRate{ sr }, channels { ch }, frameCount{ frames }
    {}
};
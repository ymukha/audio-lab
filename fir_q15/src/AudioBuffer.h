#pragma once

#include <vector>

template<class T>
struct AudioBuffer
{
    size_t sampleRate{ 48000 };
    size_t channels{ 2 };
    size_t frameCount{ 1 };
    std::vector<T> data;

    AudioBuffer() = default;
    
    AudioBuffer(size_t sr, size_t ch, size_t frames)
        : sampleRate{ sr }, channels { ch }, frameCount{ frames }
    {}
};
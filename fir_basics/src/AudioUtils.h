#pragma once

struct AudioBuffer;


AudioBuffer makeSine(float frequency,
                     float amplitude,
                     float durationSeconds,
                     size_t sampleRate,
                     size_t channels);
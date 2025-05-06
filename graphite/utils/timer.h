#pragma once

#include <cstdint>

class Timer
{
public:
    Timer();

    void Start();
    float GetDeltaTime();

private: // members
    int64_t m_frequency = 0;
    int64_t m_lastTime = 0;
};

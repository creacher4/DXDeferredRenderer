#include "timer.h"
#include <Windows.h>

using namespace Graphite::Utils;

Timer::Timer()
{
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&m_frequency));
}

void Timer::Start()
{
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&m_lastTime));
}

float Timer::GetDeltaTime()
{
    int64_t currentTime = 0;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&currentTime));
    float deltaTime = static_cast<float>(currentTime - m_lastTime) / static_cast<float>(m_frequency);
    m_lastTime = currentTime;
    return deltaTime;
}
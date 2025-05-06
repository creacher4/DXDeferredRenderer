#pragma once

#include <cstdint>

namespace Graphite::Utils
{
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

} // namespace Graphite::Utils
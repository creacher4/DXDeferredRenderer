#pragma once

#include "platform/win32/window.h"
#include "utils/timer.h"
#include <memory>

namespace Graphite::Core
{

    class Engine
    {
    public:
        bool Initialize(HINSTANCE hInstance, int nCmdShow);
        void Run();
        void Tick(float dt);

    public: // getters
        float GetDeltaTime() const { return m_deltaTime; }

    private: // members
        std::unique_ptr<Graphite::Platform::Window> m_window;

        // timer owned by the engine
        Graphite::Utils::Timer m_timer;
        float m_deltaTime = 0.0f;
    };

} // namespace Graphite::Core
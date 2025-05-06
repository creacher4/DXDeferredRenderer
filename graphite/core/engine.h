#pragma once

#include "platform/win32/window.h"
#include "gfx/render_backend.h"
#include "utils/timer.h"
#include <memory>

class Engine
{
public:
    bool Initialize(HINSTANCE hInstance, int nCmdShow);
    void Run();
    void Tick(float dt);

    void Shutdown();

public: // getters
    float GetDeltaTime() const { return m_deltaTime; }

private: // members
    std::unique_ptr<Window> m_window;

    // timer owned by the engine
    Timer m_timer;
    float m_deltaTime = 0.0f;

    std::unique_ptr<RenderBackend> m_renderBackend;
};

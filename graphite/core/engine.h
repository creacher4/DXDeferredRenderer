#pragma once

#include "platform/win32/window.h"
#include "gfx/backend/render_backend.h"
#include "utils/timer.h"
#include <memory>

class Engine
{
public:
    // engine will either create its own window
    bool Initialize(HINSTANCE hInstance, int nCmdShow);
    // or have a dependency injected window where the caller provides the window
    bool Initialize(std::unique_ptr<Window> window, HINSTANCE hInstance, int nCmdShow);

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

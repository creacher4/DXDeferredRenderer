#include "engine.h"
#include "utils/debug.h"

using namespace Graphite::Core;

bool Engine::Initialize(
    HINSTANCE hInstance,
    int nCmdShow)
{
    m_window = std::make_unique<Graphite::Platform::Window>();
    if (!m_window->Initialize(hInstance, nCmdShow))
        return false;

    // initialize the timer
    m_timer.Start();

    return true;
}

void Engine::Run()
{
    MSG msg = {};
    while (true)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        m_deltaTime = m_timer.GetDeltaTime();
        Tick(m_deltaTime);
    }
}

void Engine::Tick(float dt)
{
    // for now, just output a debug message
    // make sure it works

    // only output every second,
    // that way less work on cpu and wont freeze the app

    static float fpsTimer = 0.0f;
    static int frameCount = 0;

    fpsTimer += dt;
    frameCount++;

    if (fpsTimer >= 1.0f)
    {
        // output the FPS
        std::string msg = "FPS: " + std::to_string(frameCount) + "\n";
        GP_DEBUG_STR(msg);
        fpsTimer = 0.0f;
        frameCount = 0;
    }
}
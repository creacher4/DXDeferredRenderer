#include "engine.h"
#include "utils/debug.h"
#include "gfx/render_backend_factory.h"

bool Engine::Initialize(
    HINSTANCE hInstance,
    int nCmdShow)
{
    m_window = std::make_unique<Window>();
    if (!m_window->Initialize(hInstance, nCmdShow))
        return false;

    // initialize the timer
    m_timer.Start();

    int width = m_window->GetWidth();
    int height = m_window->GetHeight();

    // initialize the render backend
    m_renderBackend = CreateRenderBackend();
    if (!m_renderBackend->Initialize(m_window->GetHandle(), width, height))
    {
        GP_MSGBOX_ERROR(L"Error", L"Render backend initialization failed");
        return false;
    }

    // set the viewport to the window size
    m_renderBackend->SetViewport(width, height);

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

    // update the window
    m_renderBackend->BeginFrame();
    m_renderBackend->Clear(0.2f, 0.2f, 0.2f, 1.0f); // clear to blue
    m_renderBackend->EndFrame();
}

void Engine::Shutdown()
{
    if (m_renderBackend)
    {
        m_renderBackend->Shutdown();
    }
}
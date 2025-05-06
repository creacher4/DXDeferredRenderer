#include "engine.h"
#include "utils/debug.h"

#include <Windows.h>

using namespace Graphite::Core;

bool Engine::Initialize(
    HINSTANCE hInstance,
    int nCmdShow)
{
    m_window = std::make_unique<Graphite::Platform::Window>();
    if (!m_window->Initialize(hInstance, nCmdShow))
        return false;

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

        Tick();
    }
}

void Engine::Tick()
{
    // for now, just output a debug message
    // make sure it works
    GP_DEBUG("Tick called\n");
}
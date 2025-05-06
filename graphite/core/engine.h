#pragma once

#include <memory>
#include "platform/win32/window.h"

namespace Graphite::Core
{

    class Engine
    {
    public:
        bool Initialize(HINSTANCE hInstance, int nCmdShow);
        void Run();
        void Tick();

    private: // members
        std::unique_ptr<Graphite::Platform::Window> m_window;
    };

} // namespace Graphite::Core
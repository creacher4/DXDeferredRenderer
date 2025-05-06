#pragma once

#include <Windows.h>

namespace Graphite::Platform
{

    class Window
    {
    public:
        Window();
        ~Window();

        bool Initialize(HINSTANCE hInstance, int nCmdShow);
        void MainLoop();

        HWND GetHandle() const { return m_hwnd; }

    private: // helpers
        bool RegisterWindowClass(HINSTANCE hInstance);
        bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow);

        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT HandleInstanceMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    private: // members
        HWND m_hwnd = nullptr;
        static constexpr const wchar_t *kWindowClassName = L"GraphiteWindowClass";
    };

} // namespace Graphite::Platform
#include "window.h"

using namespace Graphite::Platform;

Window::Window() = default;

Window::~Window()
{
    if (m_hwnd)
    {
        DestroyWindow(m_hwnd);
    }
    UnregisterClass(kWindowClassName, GetModuleHandle(nullptr));
}

bool Window::Initialize(
    HINSTANCE hInstance,
    int nCmdShow)
{
    if (!RegisterWindowClass(hInstance))
        return false;
    return CreateMainWindow(hInstance, nCmdShow);
}

bool Window::RegisterWindowClass(
    HINSTANCE hInstance)
{
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = kWindowClassName;

    if (!RegisterClassEx(&wc))
    {
        MessageBox(nullptr, L"RegisterClassEx failed", L"Error", MB_OK | MB_ICONERROR);
        return false;
    };

    return true;
}

bool Window::CreateMainWindow(
    HINSTANCE hInstance,
    int nCmdShow)
{
    m_hwnd = CreateWindowEx(
        0,
        kWindowClassName,
        L"Graphite Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1280, 720,
        nullptr,
        nullptr,
        hInstance,
        this // pass the instance of the Window class as user data
    );

    if (!m_hwnd)
    {
        MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK | MB_ICONERROR);
        return false;
    }

    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);

    return true;
}

void Window::MainLoop()
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

        // whatever
    }
}

LRESULT CALLBACK Window::WindowProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    Window *pWindow = nullptr;

    if (msg == WM_NCCREATE)
    {
        // store the pointer to the Window instance in the user data of the window
        CREATESTRUCT *create = reinterpret_cast<CREATESTRUCT *>(lParam);
        pWindow = reinterpret_cast<Window *>(create->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
    }
    else
    {
        pWindow = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pWindow)
    {
        // handle messages for the window instance
        return pWindow->HandleInstanceMessage(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Window::HandleInstanceMessage(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
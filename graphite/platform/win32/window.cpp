#include "window.h"
#include "utils/debug.h"

Window::Window() = default;

Window::~Window()
{
    if (m_hwnd)
    {
        DestroyWindow(m_hwnd); // destroy first
        UnregisterClass(s_WindowClassName, m_hInstance);
    }
}

bool Window::Initialize(
    HINSTANCE hInstance,
    int nCmdShow,
    int width,
    int height,
    const wchar_t *title)
{
    m_width = width;
    m_height = height;
    m_title = title;

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
    wc.lpszClassName = s_WindowClassName;

    if (!RegisterClassEx(&wc))
    {
        GP_MSGBOX_ERROR(L"Error", L"RegisterClassEx failed");
        return false;
    };

    return true;
}

bool Window::CreateMainWindow(
    HINSTANCE hInstance,
    int nCmdShow)
{
    RECT rect = {0, 0, m_width, m_height};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    m_hwnd = CreateWindowEx(
        0,
        s_WindowClassName,
        m_title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        windowWidth, windowHeight,
        nullptr,
        nullptr,
        hInstance,
        this // pass the instance of the Window class as user data
    );

    if (!m_hwnd)
    {
        GP_MSGBOX_ERROR(L"Error", L"CreateWindowEx failed");
        return false;
    }

    ShowWindow(m_hwnd, nCmdShow);
    UpdateWindow(m_hwnd);

    return true;
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
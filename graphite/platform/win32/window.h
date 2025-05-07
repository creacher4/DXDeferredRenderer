#pragma once

#include <Windows.h>

class Window
{
public:
    Window();
    ~Window();

    // non copyable
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    // compile time defaults
    static constexpr int DefaultWidth = 1280;
    static constexpr int DefaultHeight = 720;
    static constexpr const wchar_t *DefaultTitle = L"Graphite Engine";

    // set defaults
    // consider using constructor instead
    bool Initialize(
        HINSTANCE hInstance,
        int nCmdShow,
        int width = DefaultWidth,
        int height = DefaultHeight,
        const wchar_t *title = DefaultTitle);

public: // getters
    HWND GetHandle() const { return m_hwnd; }
    HINSTANCE GetInstance() const { return m_hInstance; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    const wchar_t *GetTitle() const { return m_title; }

private: // helpers
    bool RegisterWindowClass(HINSTANCE hInstance);
    bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleInstanceMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private: // members
    HWND m_hwnd = nullptr;
    HINSTANCE m_hInstance = nullptr;

    // window class
    static constexpr const wchar_t *s_WindowClassName = L"GraphiteWindowClass";

    int m_width;
    int m_height;
    const wchar_t *m_title;
};
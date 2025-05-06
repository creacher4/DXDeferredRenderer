#include "platform/win32/window.h"
#include <cstdlib>

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE /*hPrevInstance*/,
    PWSTR /*pCmdLine*/,
    int nCmdShow)
{
    MessageBox(nullptr, L"wWinMain called", L"Debug", MB_OK | MB_ICONINFORMATION);
    Graphite::Platform::Window window;

    if (!window.Initialize(hInstance, nCmdShow))
    {
        MessageBox(nullptr, L"Failed to initialize window", L"Error", MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }

    window.MainLoop();
    return EXIT_SUCCESS;
}

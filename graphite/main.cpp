#include "core/engine.h"
#include "utils/debug.h"
#include <cstdlib>

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE /*hPrevInstance*/,
    PWSTR /*pCmdLine*/,
    int nCmdShow)
{
    GP_MSGBOX_INFO(L"Debug", L"wWinMain called");
    Graphite::Core::Engine engine;

    if (!engine.Initialize(hInstance, nCmdShow))
    {
        GP_MSGBOX_ERROR(L"Error", L"Failed to initialize the engine");
        return EXIT_FAILURE;
    }

    engine.Run();
    return EXIT_SUCCESS;
}

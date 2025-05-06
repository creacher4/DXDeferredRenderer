#pragma once

#include <Windows.h>
#include <string>

#define GP_MSGBOX_INFO(title, text) \
    MessageBox(nullptr, text, title, MB_OK | MB_ICONINFORMATION)

#define GP_MSGBOX_ERROR(title, text) \
    MessageBox(nullptr, text, title, MB_OK | MB_ICONERROR)

#define GP_DEBUG(msg) \
    OutputDebugStringA(msg)

#define GP_DEBUG_STR(msg) \
    OutputDebugStringA((msg).c_str())

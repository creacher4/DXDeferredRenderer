#pragma once

#include <Windows.h>
#include <string>

#ifdef _DEBUG
#define GP_MSGBOX_INFO(title, text) \
    MessageBox(nullptr, text, title, MB_OK | MB_ICONINFORMATION)

#define GP_MSGBOX_ERROR(title, text) \
    MessageBox(nullptr, text, title, MB_OK | MB_ICONERROR)

#define GP_DEBUG(msg) \
    OutputDebugStringA(msg)

#define GP_DEBUG_STR(msg) \
    OutputDebugStringA((msg).c_str())

#else
#define GP_MSGBOX_INFO(title, text) ((void)0)
#define GP_MSGBOX_ERROR(title, text) ((void)0)
#define GP_DEBUG(msg) ((void)0)
#define GP_DEBUG_STR(msg) ((void)0)
#endif

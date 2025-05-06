#pragma once

#include <Windows.h>

class RenderBackend
{
public:
    virtual ~RenderBackend() = default;

    virtual bool Initialize(HWND hwnd, int width, int height) = 0;
    virtual void Shutdown() = 0;

    virtual void BeginFrame() = 0;
    virtual void Clear(float r, float g, float b, float a) = 0;
    virtual void EndFrame() = 0;

    virtual void SetViewport(int width, int height) = 0;
};

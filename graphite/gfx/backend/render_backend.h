#pragma once

#include <Windows.h>
#include "gfx/common/texture_desc.h"
#include "gfx/common/buffer_desc.h"

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

    virtual void BeginGBufferPass() = 0;
    virtual void BeginLightingPass() = 0;

    virtual bool CreateTexture(TextureHandle handle, const TextureDesc &desc) = 0;
    virtual void DestroyTexture(TextureHandle handle) = 0;

    // buffers
    virtual bool CreateBuffer(BufferHandle handle, const BufferDesc &desc, const void *initialData = nullptr) = 0;
    virtual void DestroyBuffer(BufferHandle handle) = 0;

    // set buffers
    virtual void BindVertexBuffer(BufferHandle handle, uint32_t stride, uint32_t offset) = 0;
    virtual void BindIndexBuffer(BufferHandle handle, IndexFormat format, uint32_t offset) = 0;
    virtual void DrawIndexed(uint32_t indexCount, uint32_t startIndex = 0, int32_t baseVertex = 0) = 0;
};

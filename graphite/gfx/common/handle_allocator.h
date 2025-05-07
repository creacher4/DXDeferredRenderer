#pragma once

#include <atomic>
#include "gfx/common/buffer_desc.h"
#include "gfx/common/texture_desc.h"

class HandleAllocator
{
public:
    static BufferHandle NextBufferHandle()
    {
        return static_cast<BufferHandle>(s_bufferCounter.fetch_add(1, std::memory_order_relaxed));
    }

    static TextureHandle NextTextureHandle()
    {
        return static_cast<TextureHandle>(s_textureCounter.fetch_add(1, std::memory_order_relaxed));
    }

private:
    static std::atomic<BufferHandle> s_bufferCounter;
    static std::atomic<TextureHandle> s_textureCounter;
};
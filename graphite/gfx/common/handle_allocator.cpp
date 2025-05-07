#include "gfx/common/handle_allocator.h"

std::atomic<BufferHandle> HandleAllocator::s_bufferCounter{1u};
std::atomic<TextureHandle> HandleAllocator::s_textureCounter{1u};
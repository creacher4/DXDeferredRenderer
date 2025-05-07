#pragma once

#include <cstdint>

using TextureHandle = uint32_t;
constexpr TextureHandle InvalidTextureHandle = 0;

enum class TextureFormat
{
    UNKNOWN = 0,
    R8G8B8A8_UNORM,
    R16G16B16A16_FLOAT,
    D24_UNORM_S8_UINT,
    D32_FLOAT,
};

enum class TextureUsage : uint32_t
{
    NONE = 0,
    RENDER_TARGET = 1 << 0,
    DEPTH_STENCIL = 1 << 1,
    SHADER_RESOURCE = 1 << 2,
};

inline TextureUsage operator|(TextureUsage a, TextureUsage b)
{
    return static_cast<TextureUsage>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline bool operator&(TextureUsage a, TextureUsage b)
{
    return (static_cast<uint32_t>(a) & static_cast<uint32_t>(b)) != 0;
}

struct TextureDesc
{
    uint32_t width = 0;
    uint32_t height = 0;

    TextureFormat format = TextureFormat::UNKNOWN;
    TextureUsage usage = TextureUsage::NONE;
    uint32_t mipLevels = 1;

    // TODO: add sample count, initial data, array layers, etc.
};
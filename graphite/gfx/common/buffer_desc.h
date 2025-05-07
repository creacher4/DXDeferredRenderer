#pragma once

#include <cstdint>

using BufferHandle = uint32_t;
constexpr BufferHandle InvalidBufferHandle = 0;

enum class BufferType
{
    VERTEX,
    INDEX,
    CONSTANT
};

enum class IndexFormat
{
    UINT16,
    UINT32
};

struct BufferDesc
{
    uint32_t size = 0;
    BufferType type = BufferType::VERTEX;
    bool isDynamic = false;
};
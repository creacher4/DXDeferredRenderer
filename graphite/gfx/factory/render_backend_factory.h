#pragma once

#include <memory>

enum class BackendType
{
    DX11,
    // add more backends here
};

class RenderBackend;
std::unique_ptr<RenderBackend> CreateRenderBackend(BackendType type = BackendType::DX11);

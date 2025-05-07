#include "gfx/factory/render_backend_factory.h"
#include "gfx/backend/dx11/dx11.h"

std::unique_ptr<RenderBackend> CreateRenderBackend(BackendType type)
{
    switch (type)
    {
    case BackendType::DX11:
        return std::make_unique<DX11>();
    default:
        // default to dx11
        return std::make_unique<DX11>();
    }
}
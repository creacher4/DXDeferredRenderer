#include "gfx/factory/render_backend_factory.h"
#include "gfx/backend/dx11/dx11.h"

std::unique_ptr<RenderBackend> CreateRenderBackend()
{
    return std::make_unique<DX11>();
}

#include "render_backend_factory.h"
#include "dx11_render_backend.h"

std::unique_ptr<RenderBackend> CreateRenderBackend()
{
    return std::make_unique<DX11RenderBackend>();
}

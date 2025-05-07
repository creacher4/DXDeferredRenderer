#include "gfx/backend/dx11/helpers/dx11_gbuffer.h"

bool DX11GBuffer::Initialize(DX11TextureManager *texManager, int width, int height)
{
    m_texManager = texManager;

    TextureDesc rt = {
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height),
        TextureFormat::R8G8B8A8_UNORM,
        TextureUsage::RENDER_TARGET | TextureUsage::SHADER_RESOURCE,
        1};
    texManager->CreateTexture(m_albedo, rt);
    texManager->CreateTexture(m_normal, rt);
    texManager->CreateTexture(m_orm, rt);

    TextureDesc depth = {
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height),
        TextureFormat::D24_UNORM_S8_UINT,
        TextureUsage::DEPTH_STENCIL,
        1};
    texManager->CreateTexture(m_depth, depth);

    return true;
}

void DX11GBuffer::Shutdown()
{
    if (!m_texManager)
        return;

    m_texManager->DestroyTexture(m_albedo);
    m_texManager->DestroyTexture(m_normal);
    m_texManager->DestroyTexture(m_orm);
    m_texManager->DestroyTexture(m_depth);
}

void DX11GBuffer::BindForWriting(ID3D11DeviceContext *context)
{
    auto albedo = m_texManager->GetTexture(m_albedo);
    auto normal = m_texManager->GetTexture(m_normal);
    auto orm = m_texManager->GetTexture(m_orm);
    auto depth = m_texManager->GetTexture(m_depth);

    ID3D11RenderTargetView *rtvs[] = {
        albedo->rtv.Get(),
        normal->rtv.Get(),
        orm->rtv.Get()};

    context->OMSetRenderTargets(3, rtvs, depth->dsv.Get());

    D3D11_VIEWPORT viewport = {};
    viewport.Width = static_cast<float>(albedo->desc.width);
    viewport.Height = static_cast<float>(albedo->desc.height);
    viewport.MaxDepth = 1.0f;

    context->RSSetViewports(1, &viewport);
}
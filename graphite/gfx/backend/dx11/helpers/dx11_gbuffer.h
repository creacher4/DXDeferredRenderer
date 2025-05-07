#pragma once

#include "gfx/common/texture_desc.h"
#include "gfx/backend/dx11/helpers/dx11_texture_manager.h"

enum GBufferTextureID : TextureHandle
{
    GBUFFER_ALBEDO = 1u,
    GBUFFER_NORMAL = 2u,
    GBUFFER_ORM = 3u,
    GBUFFER_DEPTH = 4u,
};

class DX11GBuffer
{
public:
    bool Initialize(DX11TextureManager *texManager, int width, int height);
    void Shutdown();
    void BindForWriting(ID3D11DeviceContext *context);

private: // members
    TextureHandle m_albedo = GBUFFER_ALBEDO;
    TextureHandle m_normal = GBUFFER_NORMAL;
    TextureHandle m_orm = GBUFFER_ORM;
    TextureHandle m_depth = GBUFFER_DEPTH;

    DX11TextureManager *m_texManager = nullptr;
};
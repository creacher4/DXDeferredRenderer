#pragma once

#include "gfx/common/texture_desc.h"
#include "gfx/backend/dx11/helpers/dx11_texture_manager.h"

class DX11GBuffer
{
public:
    bool Initialize(DX11TextureManager *texManager, int width, int height);
    void Shutdown(DX11TextureManager *texManager);
    void BindForWriting(ID3D11DeviceContext *context);

private: // members
    TextureHandle m_albedo = 1;
    TextureHandle m_normal = 2;
    TextureHandle m_orm = 3;
    TextureHandle m_depth = 4;

    DX11TextureManager *m_texManager = nullptr;
};
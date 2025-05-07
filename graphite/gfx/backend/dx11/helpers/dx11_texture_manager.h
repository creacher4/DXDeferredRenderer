#pragma once

#include <d3d11.h>
#include <wrl/client.h>
#include <unordered_map>
#include "gfx/common/texture_desc.h"

struct DX11Texture
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

    TextureDesc desc;
};

class DX11TextureManager
{
public:
    DX11TextureManager() = default;

    void Initialize(ID3D11Device *device);
    void Shutdown();

    bool CreateTexture(TextureHandle handle, const TextureDesc &desc);
    void DestroyTexture(TextureHandle handle);

public: // getters
    DX11Texture *GetTexture(TextureHandle handle);

private: // members
    Microsoft::WRL::ComPtr<ID3D11Device> m_device;
    std::unordered_map<TextureHandle, DX11Texture> m_textures;
};
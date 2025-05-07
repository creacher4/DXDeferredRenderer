#include "gfx/backend/dx11/helpers/dx11_texture_manager.h"
#include "utils/debug.h"

void DX11TextureManager::Initialize(ID3D11Device *device)
{
    m_device = device;
}

void DX11TextureManager::Shutdown()
{
    m_textures.clear();
}

bool DX11TextureManager::CreateTexture(TextureHandle handle, const TextureDesc &desc)
{
    if (m_textures.count(handle) > 0)
    {
        GP_DEBUG_STR("CreateTexture failed: texture already exists: " + std::to_string(handle));
        return false;
    }

    DX11Texture tex;
    tex.desc = desc;

    D3D11_TEXTURE2D_DESC td = {};
    td.Width = desc.width;
    td.Height = desc.height;
    td.MipLevels = desc.mipLevels;
    td.ArraySize = 1;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.Format = DXGI_FORMAT_UNKNOWN;

    switch (desc.format)
    {
    case TextureFormat::R8G8B8A8_UNORM:
        td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        break;
    case TextureFormat::R16G16B16A16_FLOAT:
        td.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
        break;
    case TextureFormat::D24_UNORM_S8_UINT:
        td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        break;
    case TextureFormat::D32_FLOAT:
        td.Format = DXGI_FORMAT_D32_FLOAT;
        break;
    default:
        return false;
    }

    td.BindFlags = 0;
    if (desc.usage & TextureUsage::RENDER_TARGET)
        td.BindFlags |= D3D11_BIND_RENDER_TARGET;
    if (desc.usage & TextureUsage::DEPTH_STENCIL)
        td.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
    if (desc.usage & TextureUsage::SHADER_RESOURCE)
        td.BindFlags |= D3D11_BIND_SHADER_RESOURCE;

    HRESULT hr = m_device->CreateTexture2D(&td, nullptr, tex.texture.GetAddressOf());
    if (FAILED(hr))
    {
        GP_DEBUG_STR("CreateTexture2D failed: " + std::to_string(handle));
        return false;
    }

    if (desc.usage & TextureUsage::RENDER_TARGET)
        m_device->CreateRenderTargetView(tex.texture.Get(), nullptr, tex.rtv.GetAddressOf());
    if (desc.usage & TextureUsage::DEPTH_STENCIL)
        m_device->CreateDepthStencilView(tex.texture.Get(), nullptr, tex.dsv.GetAddressOf());
    if (desc.usage & TextureUsage::SHADER_RESOURCE)
        m_device->CreateShaderResourceView(tex.texture.Get(), nullptr, tex.srv.GetAddressOf());

    m_textures[handle] = std::move(tex);
    return true;
}

void DX11TextureManager::DestroyTexture(TextureHandle handle)
{
    if (m_textures.erase(handle) == 0)
    {
        GP_DEBUG_STR("DestroyTexture failed: texture not found: " + std::to_string(handle));
    }
}

DX11Texture *DX11TextureManager::GetTexture(TextureHandle handle)
{
    auto it = m_textures.find(handle);
    return (it != m_textures.end()) ? &it->second : nullptr;
}
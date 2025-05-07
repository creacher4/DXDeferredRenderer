#pragma once

#include "gfx/backend/render_backend.h"
#include "gfx/backend/dx11/helpers/dx11_texture_manager.h"
#include "gfx/backend/dx11/helpers/dx11_gbuffer.h"
#include "gfx/backend/dx11/helpers/dx11_buffer_manager.h"
#include <d3d11.h>
#include <wrl/client.h>

class DX11 : public RenderBackend
{
public:
    DX11();
    ~DX11() override;

    bool Initialize(HWND hwnd, int width, int height) override;
    void Shutdown() override;

    void BeginFrame() override;
    void Clear(float r, float g, float b, float a) override;
    void EndFrame() override;

    void SetViewport(int width, int height) override;

    void BeginGBufferPass() override;
    void BeginLightingPass() override;

    bool CreateTexture(TextureHandle handle, const TextureDesc &desc) override;
    void DestroyTexture(TextureHandle handle) override;

    bool CreateBuffer(BufferHandle handle, const BufferDesc &desc, const void *initialData = nullptr) override;
    void DestroyBuffer(BufferHandle handle) override;

    void BindVertexBuffer(BufferHandle handle, uint32_t stride, uint32_t offset) override;
    void BindIndexBuffer(BufferHandle handle, IndexFormat format, uint32_t offset) override;
    void DrawIndexed(uint32_t indexCount, uint32_t startIndex = 0, int32_t baseVertex = 0) override;

private: // members
    DX11TextureManager m_textureManager;
    DX11BufferManager m_bufferManager;
    DX11GBuffer m_gbuffer;

    Microsoft::WRL::ComPtr<ID3D11Device> m_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

    DXGI_SWAP_CHAIN_DESC m_swapChainDesc = {};
};
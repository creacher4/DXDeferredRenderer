#pragma once

#include "render_backend.h"
#include <d3d11.h>
#include <wrl/client.h>

class DX11RenderBackend : public RenderBackend
{
public:
    DX11RenderBackend();
    ~DX11RenderBackend() override;

    bool Initialize(HWND hwnd, int width, int height) override;
    void Shutdown() override;

    void BeginFrame() override;
    void Clear(float r, float g, float b, float a) override;
    void EndFrame() override;

    void SetViewport(int width, int height) override;

private: // members
    Microsoft::WRL::ComPtr<ID3D11Device> m_device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
};
#include "gfx/backend/dx11/dx11.h"
#include "utils/debug.h"
#include <cassert>

DX11::DX11() = default;

DX11::~DX11()
{
    Shutdown();
}

bool DX11::Initialize(HWND hwnd, int width, int height)
{
    // create device and swap chain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    /// to use later
    m_swapChainDesc = swapChainDesc;

    UINT createFlags = 0;
#if defined(_DEBUG)
    createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0};

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &swapChainDesc,
        m_swapChain.GetAddressOf(),
        m_device.GetAddressOf(),
        &featureLevel,
        m_context.GetAddressOf());

    if (FAILED(hr))
    {
        GP_MSGBOX_ERROR(L"Error", L"D3D11CreateDeviceAndSwapChain failed");
        return false;
    }
    else
    {
        GP_DEBUG("[DX11::Initialize] - Device and Swap Chain created");
    }

    m_textureManager.Initialize(m_device.Get());
    GP_DEBUG("[DX11::Initialize] - Texture Manager initialized");
    m_gbuffer.Initialize(&m_textureManager, width, height);
    GP_DEBUG("[DX11::Initialize] - GBuffer initialized");
    m_bufferManager.Initialize(m_device.Get());
    GP_DEBUG("[DX11::Initialize] - Buffer Manager initialized");

    // create back buffer render target view
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(backBuffer.GetAddressOf()));
    if (FAILED(hr))
    {
        GP_MSGBOX_ERROR(L"Error", L"GetBuffer failed");
        return false;
    }

    hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf());
    if (FAILED(hr))
    {
        GP_MSGBOX_ERROR(L"Error", L"CreateRenderTargetView failed");
        return false;
    }
    else
    {
        GP_DEBUG("[DX11::Initialize] - Back buffer render target view created");
    }

    return true;
}

void DX11::SetViewport(int width, int height)
{
    assert(m_context);

    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = static_cast<FLOAT>(width);
    viewport.Height = static_cast<FLOAT>(height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_context->RSSetViewports(1, &viewport);
}

void DX11::BeginFrame()
{
    assert(m_context && m_renderTargetView);
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);
}

void DX11::Clear(float r, float g, float b, float a)
{
    assert(m_context && m_renderTargetView);

    const FLOAT clearColor[] = {r, g, b, a};
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
}

void DX11::EndFrame()
{
    assert(m_swapChain);

    HRESULT hr = m_swapChain->Present(1, 0);
    if (FAILED(hr))
    {
        GP_MSGBOX_ERROR(L"Error", L"Present failed");
    }
}

void DX11::Shutdown()
{
    if (!m_device)
        return;

    m_gbuffer.Shutdown();
    m_textureManager.Shutdown();
    m_bufferManager.Shutdown();
    GP_DEBUG("[DX11::Shutdown] - Texture Manager, GBuffer and Buffer Manager shut down");

    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_context.Reset();
    m_device.Reset();

    GP_DEBUG("[DX11::Shutdown] - Resources Released");
}

void DX11::BeginGBufferPass()
{
    m_gbuffer.BindForWriting(m_context.Get());
    GP_DEBUG("[DX11::BeginGBufferPass] - Bound GBuffer targets");
}

void DX11::BeginLightingPass()
{
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);
    SetViewport(m_swapChainDesc.BufferDesc.Width, m_swapChainDesc.BufferDesc.Height);
    GP_DEBUG("[DX11::BeginLightingPass] - Bound back buffer render target view");
}

bool DX11::CreateTexture(TextureHandle handle, const TextureDesc &desc)
{
    return m_textureManager.CreateTexture(handle, desc);
}

void DX11::DestroyTexture(TextureHandle handle)
{
    m_textureManager.DestroyTexture(handle);
}

bool DX11::CreateBuffer(BufferHandle handle, const BufferDesc &desc, const void *initialData)
{
    return m_bufferManager.CreateBuffer(handle, desc, initialData);
}

void DX11::DestroyBuffer(BufferHandle handle)
{
    m_bufferManager.DestroyBuffer(handle);
}

// stub
void DX11::BindVertexBuffer(BufferHandle handle, uint32_t stride, uint32_t offset)
{
    DX11Buffer *buffer = m_bufferManager.GetBuffer(handle);
    if (!buffer)
    {
        GP_DEBUG_STR("BindVertexBuffer failed: buffer not found " + std::to_string(handle));
        return;
    }

    ID3D11Buffer *vb = buffer->buffer.Get();
    m_context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
}

// stub
void DX11::BindIndexBuffer(BufferHandle handle, IndexFormat format, uint32_t offset)
{
    DX11Buffer *buffer = m_bufferManager.GetBuffer(handle);
    if (!buffer)
    {
        GP_DEBUG_STR("BindIndexBuffer failed: buffer not found " + std::to_string(handle));
        return;
    }

    DXGI_FORMAT dxgiFormat = (format == IndexFormat::UINT16) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
    ID3D11Buffer *ib = buffer->buffer.Get();
    m_context->IASetIndexBuffer(ib, dxgiFormat, offset);
}

// stub
void DX11::DrawIndexed(uint32_t indexCount, uint32_t startIndex, int32_t baseVertex)
{
    m_context->DrawIndexed(indexCount, startIndex, baseVertex);
}
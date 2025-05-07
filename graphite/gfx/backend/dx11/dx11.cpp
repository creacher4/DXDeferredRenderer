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
    GP_DEBUG("[DX11::Shutdown] - Texture Manager and GBuffer shut down");

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

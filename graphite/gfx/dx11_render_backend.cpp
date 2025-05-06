#include "dx11_render_backend.h"
#include "utils/debug.h"
#include <cassert>

DX11RenderBackend::DX11RenderBackend() = default;

DX11RenderBackend::~DX11RenderBackend()
{
    Shutdown();
}

bool DX11RenderBackend::Initialize(HWND hwnd, int width, int height)
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

    return true;
}

void DX11RenderBackend::SetViewport(int width, int height)
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

void DX11RenderBackend::BeginFrame()
{
    assert(m_context && m_renderTargetView);
    m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);
}

void DX11RenderBackend::Clear(float r, float g, float b, float a)
{
    assert(m_context && m_renderTargetView);

    const FLOAT clearColor[] = {r, g, b, a};
    m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
}

void DX11RenderBackend::EndFrame()
{
    assert(m_swapChain);

    HRESULT hr = m_swapChain->Present(1, 0);
    if (FAILED(hr))
    {
        GP_MSGBOX_ERROR(L"Error", L"Present failed");
    }
}

void DX11RenderBackend::Shutdown()
{
    m_renderTargetView.Reset();
    m_swapChain.Reset();
    m_context.Reset();
    m_device.Reset();
}

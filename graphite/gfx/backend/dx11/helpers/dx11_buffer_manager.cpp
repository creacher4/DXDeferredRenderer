#include "gfx/backend/dx11/helpers/dx11_buffer_manager.h"
#include "utils/debug.h"

void DX11BufferManager::Initialize(ID3D11Device *device)
{
    m_device = device;
}

void DX11BufferManager::Shutdown()
{
    m_buffers.clear();
}

bool DX11BufferManager::CreateBuffer(BufferHandle handle, const BufferDesc &desc, const void *initialData)
{
    if (m_buffers.count(handle) > 0)
    {
        GP_DEBUG_STR("CreateBuffer failed: handle already exists " + std::to_string(handle));
        return false;
    }

    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = desc.size;
    bd.Usage = desc.isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
    bd.BindFlags = 0;

    switch (desc.type)
    {
    case BufferType::VERTEX:
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        break;
    case BufferType::INDEX:
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        break;
    case BufferType::CONSTANT:
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        break;
    }

    bd.CPUAccessFlags = desc.isDynamic ? D3D11_CPU_ACCESS_WRITE : 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = initialData;

    DX11Buffer buffer = {};
    buffer.desc = desc;

    HRESULT hr = m_device->CreateBuffer(
        &bd,
        initialData ? &initData : nullptr,
        buffer.buffer.GetAddressOf());

    if (FAILED(hr))
    {
        GP_DEBUG_STR("CreateBuffer failed: " + std::to_string(handle));
        return false;
    }

    m_buffers[handle] = std::move(buffer);
    return true;
}

void DX11BufferManager::DestroyBuffer(BufferHandle handle)
{
    if (m_buffers.count(handle) == 0)
    {
        GP_DEBUG_STR("DestroyBuffer failed: handle not found " + std::to_string(handle));
    }
}

DX11Buffer *DX11BufferManager::GetBuffer(BufferHandle handle)
{
    auto it = m_buffers.find(handle);
    return (it != m_buffers.end()) ? &it->second : nullptr;
}
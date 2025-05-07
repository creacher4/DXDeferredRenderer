#pragma once

#include "gfx/common/buffer_desc.h"

#include <d3d11.h>
#include <wrl/client.h>
#include <unordered_map>

struct DX11Buffer
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
    BufferDesc desc;
};

class DX11BufferManager
{
public:
    void Initialize(ID3D11Device *device);
    void Shutdown();

    bool CreateBuffer(BufferHandle handle, const BufferDesc &desc, const void *initialData = nullptr);
    void DestroyBuffer(BufferHandle handle);

    DX11Buffer *GetBuffer(BufferHandle handle);

private: // members
    Microsoft::WRL::ComPtr<ID3D11Device> m_device;
    std::unordered_map<BufferHandle, DX11Buffer> m_buffers;
};

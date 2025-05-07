#pragma once

#include <memory>

class RenderBackend;
std::unique_ptr<RenderBackend> CreateRenderBackend();

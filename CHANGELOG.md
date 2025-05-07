# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- G-Buffer support with named texture attachments.
- GPU resource management for vertex, index, and constant buffers.
- Low-level draw and buffer-binding calls in the rendering API.
- Conditional debug output (enabled only in debug builds)
- Automatic handle allocator for buffer and texture IDs
- Configurable rendering backend selection
- Option to supply a custom window to the engine

### Changed

- G-Buffer attachments are cleared at the start of each pass.
- Rendering interface expanded to cover buffer and draw operations.
- Window initialization defaults now defined as compile-time constants.

### Fixed

- Buffer manager now correctly removes resources to prevent leaks.
- Improved error logging for DirectX initialization in debug mode.

## [0.0.4] - 2025-05-07

### Added

- GBuffer with multiple render targets and depth.
- Texture and GBuffer management systems.
- Separate GBuffer and lighting passes.

### Changed

- DX11 backend modularized with internal helpers.

## [0.0.3] - 2025-05-07

### Added

- Abstract `RenderBackend` interface and DX11 implementation.
- Render backend factory system.
- Engine shutdown and viewport setup.
- Basic high-res timer and FPS output.

### Changed

- `RenderBackend::Initialize` now uses window size.
- `Window` correctly sizes client area.

## [0.0.2] - 2025-05-06

### Added

- Core `Engine` class with tick-based main loop.
- Debug macros.

### Changed

- `Engine` now owns the main loop.
- `Window::Initialize` accepts width, height, and title.

### Removed

- `Window::MainLoop` replaced by engine loop.

## [0.0.1] - 2025-05-06

### Added

- Win32 window creation with message loop.
- Platform `Window` class abstraction.
- CMake setup and folder structure.
- Entry point (`wWinMain`) with minimal startup logic.

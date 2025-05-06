# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

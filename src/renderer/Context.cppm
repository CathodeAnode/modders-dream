module;
#include "GraphicsTypes.h"
export module ModdersDream.Renderer.Context;

import ModdersDream.Renderer.Diligent;
import ModdersDream.Glfw;
import ModdersDream.Logger;
import ModdersDream.Error;
import ModdersDream.Math;

import std;

export namespace ModdersDream::Renderer {

class Context : public ErrorHandler {
public:
    explicit Context(Glfw::Window& window) : window_(window) {
        Diligent::NativeWindow nativeWindow;
#ifdef __linux__
        ModdersDream::Log<ModdersDream::LogLevel::Info>("Detected linux");
        // TODO: Clean this. Maybe move it to Glfw but a bigger change may be needed, but not sure.
        // Assign window
        nativeWindow.pDisplay = Glfw::GetDisplay();
        switch (Glfw::GetPlatform()) {
            case Glfw::Platform::X11:
                nativeWindow.WindowId = static_cast<Diligent::Uint32>(
                    reinterpret_cast<std::uintptr_t>(window.GetWindow())
                );
                break;
            case Glfw::Platform::Wayland:
                // TODO: Make cursor theme not depend on XCURSOR_THEME
                nativeWindow.pWaylandSurface = window.GetWindow();
                break;
            default:
                SubmitError(
                    ModdersDream::ErrorCode::Unsupported,
                    "Unsupported window platform (only X11 and Wayland are supported)"
                );
                return;
        }

        // Create context and device
        Diligent::IEngineFactoryVk* factory = Diligent::LoadAndGetEngineFactoryVk();
        if (!factory) {
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Vulkan factory failed to initialize"
            );
            return;
        }

        Diligent::EngineVkCreateInfo engineInfo;
        factory->CreateDeviceAndContextsVk(engineInfo, &device_, &deviceContext_);
        if (!device_ || !deviceContext_) {
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Failed to create Vulkan device and context"
            );
            return;
        }
#elifdef _WIN32
        ModdersDream::Log<ModdersDream::LogLevel::Info>("Detected win32");
        // Assign window
        nativeWindow.hWnd = window.GetWindow();

        // Create context and device
        Diligent::IEngineFactoryD3d12* factory = Diligent::LoadAndGetEngineFactoryD3D12();
        if (!factory) {
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Direct3D 12 factory failed to initialize"
            )
            return;
        }

        Diligent::EngineD3d12CreateInfo engineInfo;
        factory->CreateDeviceAndContextsD3D12(engineInfo, &device_, &deviceContext_);
        if (!device_ || !deviceContext_) {
            ModdersDream::Error error{
                .system = "Renderer::Context",
                .operation = "CreateDeviceAndContextsD3D12",
                .description = "Failed to create Direct3D 12 device and context",
                .code = ModdersDream::ErrorCode::InitializationFailed
            };
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Failed to create Direct3D 12 device and context"
            );
            return;
        }
#elifdef __APPLE__
        ModdersDream::Log<ModdersDream::LogLevel::Info>("Detected apple");
        // Assign window
        nativeWindow.pNSView = window.GetWindow();

        // Create context and device
        Diligent::IEngineFactoryMtl* factory = Diligent::GetEngineFactoryMtl();
        if (!factory) {
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Metal factory failed to initialize"
            );
            return;
        }

        Diligent::EngineMtlCreateInfo engineInfo;
        factory->CreateDeviceAndContextsMtl(engineInfo, &device_, &deviceContext_);
        if (!device_ || !deviceContext_) {
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Failed to create Metal device and context"
            );
            return;
        }
#else
        ModdersDream::Log<ModdersDream::LogLevel::Error>("Detected unsupported platform or failed to detect. Only Linux (X11 and Wayland only), Windows and Apple are supported");
        SubmitError(
            ModdersDream::ErrorCode::Unsupported, 
            "Detected unsupported platform or failed to detect. Only Linux (X11 and Wayland only), Windows and Apple are supported"
        );
        return;
#endif

        // Create swap chain
        Math::Vector2i size = window.GetFramebufferSize();
        Diligent::SwapChainDesc swapChainDesc;
        swapChainDesc.Width = static_cast<Diligent::Uint32>(std::max(size.x(), 1));
        swapChainDesc.Height = static_cast<Diligent::Uint32>(std::max(size.y(), 1));
        swapChainDesc.DepthBufferFormat = Diligent::TextureFormat::TEX_FORMAT_UNKNOWN;

        factory->CreateSwapChainVk(device_, deviceContext_, swapChainDesc, nativeWindow, &swapChain_);
        if (!swapChain_) {
            SubmitError(
                ModdersDream::ErrorCode::InitializationFailed,
                "Failed to create swap chain"
            );
            return;
        }
    }

    ~Context() {
        deviceContext_->WaitForIdle();
    }

    void Resize() {
        Math::Vector2i size = window_.GetFramebufferSize();

        const Diligent::SwapChainDesc& desc = swapChain_->GetDesc();
        if (desc.Width != static_cast<Diligent::Uint32>(size.x()) ||
            desc.Height != static_cast<Diligent::Uint32>(size.y())) {
            swapChain_->Resize(static_cast<Diligent::Uint32>(size.x()), static_cast<Diligent::Uint32>(size.y()));
        }
    }

    Diligent::IRenderDevice* Device() {
        return device_;
    }

    Diligent::IDeviceContext* DeviceContext() {
        return deviceContext_;
    }

    Diligent::ISwapChain* SwapChain() {
        return swapChain_;
    }

private:
    const Glfw::Window& window_;
    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> device_;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> deviceContext_;
    Diligent::RefCntAutoPtr<Diligent::ISwapChain> swapChain_;
};

} // namespace ModdersDream::Renderer

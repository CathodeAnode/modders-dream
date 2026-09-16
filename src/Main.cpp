import ModdersDream.Logger;
import ModdersDream.Glfw;
import ModdersDream.Renderer.Diligent;
import ModdersDream.Math;

import std;

using namespace ModdersDream;
namespace Diligent = ModdersDream::Renderer::Diligent;

int main() {
    Glfw::Context glfwContext;

    if (glfwContext.HasError()) {
        Logger::Log(glfwContext.GetError());
        return static_cast<int>(glfwContext.GetError().code);
    }

    Glfw::SetWindowHint(Glfw::WindowHint::ClientApi, Glfw::WindowHintValue::NoApi);

    Glfw::Window window({800, 800}, "Modder's Dream");

    if (window.HasError()) {
        Logger::Log(window.GetError());
        return static_cast<int>(window.GetError().code);
    }

    Logger rendererLogger("Renderer");
    Diligent::NativeWindow nativeWindow;
#if defined(__linux__)
    nativeWindow.pDisplay = Glfw::GetDisplay();
    switch (Glfw::GetPlatform()) {
        case Glfw::Platform::X11:
            nativeWindow.WindowId = static_cast<Diligent::Uint32>(
                reinterpret_cast<std::uintptr_t>(window.GetWindow())
            );
            break;
        case Glfw::Platform::Wayland:
            nativeWindow.pWaylandSurface = window.GetWindow();
            break;
        default:
            rendererLogger.Log(LogLevel::Fatal, "Unsupported window platform for Vulkan");
            return 1;
    }
#elif defined(_WIN32)
    nativeWindow.hWnd = window.GetWindow();
#else
    rendererLogger.Log(LogLevel::Fatal, "Native Vulkan window setup is not implemented for this platform");
    return 1;
#endif

    auto* factory = Diligent::LoadAndGetEngineFactoryVk();
    if (!factory) {
        rendererLogger.Log(LogLevel::Fatal, "Failed to load the Vulkan engine");
        return 1;
    }

    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> device;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> deviceContext;
    Diligent::EngineVkCreateInfo engineInfo;
    factory->CreateDeviceAndContextsVk(engineInfo, &device, &deviceContext);
    if (!device || !deviceContext) {
        rendererLogger.Log(LogLevel::Fatal, "Failed to create the Vulkan device and context");
        return 1;
    }

    Math::Vector2i size = window.GetFramebufferSize();

    Diligent::SwapChainDesc swapChainDesc;
    swapChainDesc.Width = static_cast<Diligent::Uint32>(std::max(size.x(), 1));
    swapChainDesc.Height = static_cast<Diligent::Uint32>(std::max(size.y(), 1));
    swapChainDesc.DepthBufferFormat = Diligent::TextureFormat::TEX_FORMAT_UNKNOWN;

    Diligent::RefCntAutoPtr<Diligent::ISwapChain> swapChain;
    factory->CreateSwapChainVk(device, deviceContext, swapChainDesc, nativeWindow, &swapChain);
    if (!swapChain) {
        rendererLogger.Log(LogLevel::Fatal, "Failed to create the Vulkan swap chain");
        return 1;
    }

    constexpr float ClearColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    bool running = true;
    while (running && !window.ShouldClose()) {
        Glfw::PollEvents();

        for (const Glfw::KeyEvent& event : window.KeyEvents()) {
            if (event.key == Glfw::Key::Escape) {
                running = false;
            }
        }
        window.ClearEvents();
        if (!running || window.ShouldClose()) {
            break;
        }

        Math::Vector2i size = window.GetFramebufferSize();
        if (size.x() <= 0 || size.y() <= 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }

        const auto& desc = swapChain->GetDesc();
        if (desc.Width != static_cast<Diligent::Uint32>(size.x()) ||
            desc.Height != static_cast<Diligent::Uint32>(size.y())) {
            swapChain->Resize(static_cast<Diligent::Uint32>(size.x()), static_cast<Diligent::Uint32>(size.y()));
        }

        auto* renderTarget = swapChain->GetCurrentBackBufferRTV();
        deviceContext->SetRenderTargets(
            1,
            &renderTarget,
            nullptr,
            Diligent::ResourceStateTransitionMode::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
        );
        deviceContext->ClearRenderTarget(
            renderTarget,
            ClearColor,
            Diligent::ResourceStateTransitionMode::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
        );
        swapChain->Present(1);
    }

    deviceContext->WaitForIdle();
    return 0;
}

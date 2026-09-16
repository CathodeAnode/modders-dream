import md.logger;
import md.glfw;
import md.renderer.diligent;
import md.math;

import std;

using namespace md;
namespace diligent = md::renderer::diligent;

int main() {
    glfw::Context glfw_context;

    if (glfw_context.has_error()) {
        Logger::log(glfw_context.get_error());
        return static_cast<int>(glfw_context.get_error().code);
    }

    glfw::window_hint(glfw::WindowHint::ClientAPI, glfw::WindowHintValue::NoAPI);

    glfw::Window window({800, 800}, "Modder's Dream");

    if (window.has_error()) {
        Logger::log(window.get_error());
        return static_cast<int>(window.get_error().code);
    }

    Logger renderer_logger("Renderer");
    diligent::NativeWindow native_window;
#if defined(__linux__)
    native_window.pDisplay = glfw::get_display();
    switch (glfw::get_platform()) {
        case glfw::Platform::X11:
            native_window.WindowId = static_cast<diligent::Uint32>(
                reinterpret_cast<std::uintptr_t>(window.get_window())
            );
            break;
        case glfw::Platform::Wayland:
            native_window.pWaylandSurface = window.get_window();
            break;
        default:
            renderer_logger.log(LogLevel::Fatal, "Unsupported window platform for Vulkan");
            return 1;
    }
#elif defined(_WIN32)
    native_window.hWnd = window.get_window();
#else
    renderer_logger.log(LogLevel::Fatal, "Native Vulkan window setup is not implemented for this platform");
    return 1;
#endif

    auto* factory = diligent::LoadAndGetEngineFactoryVk();
    if (!factory) {
        renderer_logger.log(LogLevel::Fatal, "Failed to load the Vulkan engine");
        return 1;
    }

    diligent::RefCntAutoPtr<diligent::IRenderDevice> device;
    diligent::RefCntAutoPtr<diligent::IDeviceContext> device_context;
    diligent::EngineVkCreateInfo engine_info;
    factory->CreateDeviceAndContextsVk(engine_info, &device, &device_context);
    if (!device || !device_context) {
        renderer_logger.log(LogLevel::Fatal, "Failed to create the Vulkan device and context");
        return 1;
    }

    math::Vector2i size = window.get_framebuffer_size();

    diligent::SwapChainDesc swap_chain_desc;
    swap_chain_desc.Width = static_cast<diligent::Uint32>(std::max(size.x(), 1));
    swap_chain_desc.Height = static_cast<diligent::Uint32>(std::max(size.y(), 1));
    swap_chain_desc.DepthBufferFormat = diligent::TEXTURE_FORMAT::TEX_FORMAT_UNKNOWN;

    diligent::RefCntAutoPtr<diligent::ISwapChain> swap_chain;
    factory->CreateSwapChainVk(device, device_context, swap_chain_desc, native_window, &swap_chain);
    if (!swap_chain) {
        renderer_logger.log(LogLevel::Fatal, "Failed to create the Vulkan swap chain");
        return 1;
    }

    constexpr float clear_color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    bool running = true;
    while (running && !window.should_close()) {
        glfw::poll_events();

        for (const glfw::KeyEvent& event : window.key_events()) {
            if (event.key == glfw::Key::Escape) {
                running = false;
            }
        }
        window.clear_events();
        if (!running || window.should_close()) {
            break;
        }

        math::Vector2i size = window.get_framebuffer_size();
        if (size.x() <= 0 || size.y() <= 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }

        const auto& desc = swap_chain->GetDesc();
        if (desc.Width != static_cast<diligent::Uint32>(size.x()) ||
            desc.Height != static_cast<diligent::Uint32>(size.y())) {
            swap_chain->Resize(static_cast<diligent::Uint32>(size.x()), static_cast<diligent::Uint32>(size.y()));
        }

        auto* render_target = swap_chain->GetCurrentBackBufferRTV();
        device_context->SetRenderTargets(
            1,
            &render_target,
            nullptr,
            diligent::RESOURCE_STATE_TRANSITION_MODE::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
        );
        device_context->ClearRenderTarget(
            render_target,
            clear_color,
            diligent::RESOURCE_STATE_TRANSITION_MODE::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
        );
        swap_chain->Present(1);
    }

    device_context->WaitForIdle();
    return 0;
}

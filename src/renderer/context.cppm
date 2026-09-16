export module md.renderer.context;

import md.renderer.diligent;
import md.glfw;
import md.logger;
import md.error;
import md.math;

import std;

export namespace md::renderer {

class Context : public ErrorHandler {
public:
    explicit Context(glfw::Window& window) {
        diligent::NativeWindow native_window;
#ifdef __linux__
        // TODO: Clean this. Maybe move it to glfw but a bigger change may be needed, but not sure.
        // Assign window
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
                md::Error error{
                    .system = "renderer::Context",
                    .operation = "get_platform",
                    .description = "Unsupported window platform (only X11 and Wayland are supported)",
                    .code = md::ErrorCode::Unsupported
                };
                submit_error(error);
                return;
        }

        // Create context and device
        diligent::IEngineFactoryVk* factory = diligent::LoadAndGetEngineFactoryVk();
        if (!factory) {
            md::Error error{
                .system = "renderer::Context",
                .operation = "LoadAndGetEngineFactoryVk",
                .description = "Vulkan factory failed to initialize",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }

        factory->SetMessageCallback(diligent_log);

        diligent::EngineVkCreateInfo engine_info;
        factory->CreateDeviceAndContextsVk(engine_info, &device, &device_context);
        if (!device || !device_context) {
            md::Error error{
                .system = "renderer::Context",
                .operation = "CreateDeviceAndContextsVk",
                .description = "Failed to create Vulkan device and context",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }
#elifdef _WIN32
        // Assign window
        native_window.hWnd = window.get_window();

        // Create context and device
        diligent::IEngineFactoryD3D12* factory = diligent::LoadAndGetEngineFactoryD3D12();
        if (!factory) {
            md::Error error{
                .system = "renderer::Context",
                .operation = "LoadAndGetEngineFactoryD3D12",
                .description = "Direct3D 12 factory failed to initialize",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }

        factory->SetMessageCallback(diligent_log);

        diligent::EngineD3D12CreateInfo engine_info;
        factory->CreateDeviceAndContextsD3D12(engine_info, &device, &device_context);
        if (!device || !device_context) {
            md::Error error{
                .system = "renderer::Context",
                .operation = "CreateDeviceAndContextsD3D12",
                .description = "Failed to create Direct3D 12 device and context",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }
#elifdef __APPLE__
        // Assign window
        native_window.pNSView = window.get_window();

        // Create context and device
        diligent::IEngineFactoryMtl* factory = diligent::GetEngineFactoryMtl();
        if (!factory) {
            md::Error error{
                .system = "renderer::Context",
                .operation = "GetEngineFactoryMtl",
                .description = "Metal factory failed to initialize",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }

        factory->SetMessageCallback(diligent_log);

        diligent::EngineMtlCreateInfo engine_info;
        factory->CreateDeviceAndContextsMtl(engine_info, &device, &device_context);
        if (!device || !device_context) {
            md::Error error{
                .system = "renderer::Context",
                .operation = "CreateDeviceAndContextsMtl",
                .description = "Failed to create Metal device and context",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }
#else
        md::Error error{
            .system = "renderer::Context",
            .operation = "Platform selection",
            .description = "Unsupported platform (only Linux (X11 and Wayland only), Windows and Apple are supported)",
            .code = md::ErrorCode::Unsupported
        };
        submit_error(error);
        return;
#endif

        // Create swap chain

        math::Vector2i size = window.get_framebuffer_size();
        diligent::SwapChainDesc swap_chain_desc;
        swap_chain_desc.Width = static_cast<diligent::Uint32>(std::max(size.x(), 1));
        swap_chain_desc.Height = static_cast<diligent::Uint32>(std::max(size.y(), 1));
        swap_chain_desc.DepthBufferFormat = diligent::TEXTURE_FORMAT::TEX_FORMAT_UNKNOWN;

        factory->CreateSwapChainVk(device, device_context, swap_chain_desc, native_window, &swap_chain);
        if (!swap_chain) {
            md::Error error{
                .system = "CreateSwapChainVk",
                .operation = "Swap chain creation",
                .description = "Failed to create swap chain.",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }
    }

    ~Context() = default;

private:
    diligent::RefCntAutoPtr<diligent::IRenderDevice> device;
    diligent::RefCntAutoPtr<diligent::IDeviceContext> device_context;
    diligent::RefCntAutoPtr<diligent::ISwapChain> swap_chain;

    inline static Logger logger = Logger("Diligent");
    static void diligent_log(diligent::DEBUG_MESSAGE_SEVERITY severity, const char* message, const char* function, const char* file, int line) {
        std::string type;
        switch (severity) {
            case diligent::DEBUG_MESSAGE_SEVERITY_INFO:
                break;
                type = LogLevel::Info;
            case diligent::DEBUG_MESSAGE_SEVERITY_WARNING:
                type = LogLevel::Warn;
                break;
            case diligent::DEBUG_MESSAGE_SEVERITY_ERROR:
                type = LogLevel::Error;
                break;
            case diligent::DEBUG_MESSAGE_SEVERITY_FATAL_ERROR:
                type = LogLevel::Fatal;
                break;
        }
        logger.log(type, "{} [{}:{} in {}()]", message, file, line, function);
    }
};

} // namespace md::renderer

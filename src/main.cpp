#include <bgfx/bgfx.h>

import md.logger;
import md.glfw;

import std;

using namespace md;

int main() {
    glfw::Context context;

    if (context.has_error()) {
        Logger::log(context.get_error());
        return static_cast<int>(context.get_error().code);
    }

    glfw::window_hint(glfw::WindowHint::ClientAPI, glfw::WindowHintValue::NoAPI);

    glfw::Window window(800, 800, "Modder's Dream");

    if (window.has_error()) {
        Logger::log(window.get_error());
        return static_cast<int>(window.get_error().code);
    }

    bgfx::Init init{};
    init.type = bgfx::RendererType::Count;

    if (glfw::get_platform() == glfw::Platform::Wayland) {
        init.platformData.type = bgfx::NativeWindowHandleType::Wayland;
    }

    init.swapChain.ndt = glfw::get_display();
    init.swapChain.nwh = window.get_window();

    int width, height;
    window.get_framebuffer_size(&width, &height);

    init.swapChain.width = width > 0 ? uint32_t(width) : 1;
    init.swapChain.height = height > 0 ? uint32_t(height) : 1;

    if (!bgfx::init(init)) {
        // TODO: Log here and maybe wrap around bgfx initialization a bit
        return 1;
    }

    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR, 0xff0000ff);

    bool running = true;
    while (running && !window.should_close()) {
        glfw::poll_events();

        for (const glfw::KeyEvent& event : window.key_events()) {
            if (event.key == glfw::Key::Escape) {
                running = false;
            }
        }

        bgfx::touch(0);
        bgfx::frame();
    }

    bgfx::shutdown();

    return 0;
}

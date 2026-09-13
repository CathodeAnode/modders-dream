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

    while (!window.should_close()) {
        glfw::poll_events();

        for (const glfw::KeyEvent& event : window.key_events()) {
            if (event.key == glfw::Key::Escape) {
                break;
            }
        }
    }

    return 0;
}

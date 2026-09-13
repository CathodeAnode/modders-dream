#include <bgfx/bgfx.h>

import md.logger;
import md.glfw;

import std;

using namespace md;

int main() {
    glfw::Context context;

    glfw::window_hint(glfw::WindowHint::ClientAPI, glfw::WindowHintValue::NoAPI);

    glfw::Window window(800, 800, "Modder's Dream");

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

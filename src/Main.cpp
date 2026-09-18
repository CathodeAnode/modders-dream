import ModdersDream.Logger;
import ModdersDream.Settings;
import ModdersDream.Glfw;
import ModdersDream.Math;
import ModdersDream.Renderer.Diligent;
import ModdersDream.Renderer.Context;

import std;

using namespace ModdersDream;
namespace Diligent = ModdersDream::Renderer::Diligent;

int main() {
    // For far future me: load savedata HERE
    Settings settings;

    Glfw::Context glfwContext;

    if (glfwContext.HasError()) {
        Logger::Log(glfwContext.GetError());
        return glfwContext.GetErrorCodeInt();
    }

    Glfw::SetWindowHint(Glfw::WindowHint::ClientApi, Glfw::WindowHintValue::NoApi);

    Glfw::Monitor monitor = Glfw::Monitor::Primary();

    if (monitor.HasError()) {
        Logger::Log(monitor.GetError());
        return monitor.GetErrorCodeInt();
    }

    Glfw::Window window({800, 800}, "Modder's Dream");

    if (settings.fullscreen) {
        window.SetMonitorFullscreen(monitor);
    }

    if (window.HasError()) {
        Logger::Log(window.GetError());
        return window.GetErrorCodeInt();
    }

    Renderer::Context rendererContext(window);

    if (rendererContext.HasError()) {
        Logger::Log(rendererContext.GetError());
        return rendererContext.GetErrorCodeInt();
    }

    constexpr float ClearColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
    bool running = true;
    while (running && !window.ShouldClose()) {
        window.WaitForNonzeroFramebuffer();

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

        rendererContext.Resize();

        auto* renderTarget = rendererContext.SwapChain()->GetCurrentBackBufferRTV();
        rendererContext.DeviceContext()->SetRenderTargets(
            1,
            &renderTarget,
            nullptr,
            Diligent::ResourceStateTransitionMode::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
        );
        rendererContext.DeviceContext()->ClearRenderTarget(
            renderTarget,
            ClearColor,
            Diligent::ResourceStateTransitionMode::RESOURCE_STATE_TRANSITION_MODE_TRANSITION
        );
        rendererContext.SwapChain()->Present(settings.vsync);
    }

    rendererContext.DeviceContext()->WaitForIdle();
    return 0;
}

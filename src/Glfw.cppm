module;
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
#elifdef __APPLE__
    #define GLFW_EXPOSE_NATIVE_COCOA
#elifdef __linux__
    #define GLFW_EXPOSE_NATIVE_X11
    #define GLFW_EXPOSE_NATIVE_WAYLAND
#endif
#include <GLFW/glfw3native.h>

// Undefine "True" and "False" which was defined by X11 without any prefixes
#ifdef True
    #undef True
#endif
#ifdef False
    #undef False
#endif

export module ModdersDream.Glfw;

import ModdersDream.Logger;
import ModdersDream.Error;
import ModdersDream.ZStringView;
import ModdersDream.Math;

import std;

namespace {

ModdersDream::Logger logger("GLFW");

} // namespace

export namespace ModdersDream::Glfw {

enum class Key : int {
    Space = GLFW_KEY_SPACE,
    Apostrophe = GLFW_KEY_APOSTROPHE,
    Comma = GLFW_KEY_COMMA,
    Minus = GLFW_KEY_MINUS,
    Period = GLFW_KEY_PERIOD,
    Slash = GLFW_KEY_SLASH,
    Num0 = GLFW_KEY_0,
    Num1 = GLFW_KEY_1,
    Num2 = GLFW_KEY_2,
    Num3 = GLFW_KEY_3,
    Num4 = GLFW_KEY_4,
    Num5 = GLFW_KEY_5,
    Num6 = GLFW_KEY_6,
    Num7 = GLFW_KEY_7,
    Num8 = GLFW_KEY_8,
    Num9 = GLFW_KEY_9,
    Semicolon = GLFW_KEY_SEMICOLON,
    Equal = GLFW_KEY_EQUAL,
    A = GLFW_KEY_A,
    B = GLFW_KEY_B,
    C = GLFW_KEY_C,
    D = GLFW_KEY_D,
    E = GLFW_KEY_E,
    F = GLFW_KEY_F,
    G = GLFW_KEY_G,
    H = GLFW_KEY_H,
    I = GLFW_KEY_I,
    J = GLFW_KEY_J,
    K = GLFW_KEY_K,
    L = GLFW_KEY_L,
    M = GLFW_KEY_M,
    N = GLFW_KEY_N,
    O = GLFW_KEY_O,
    P = GLFW_KEY_P,
    Q = GLFW_KEY_Q,
    R = GLFW_KEY_R,
    S = GLFW_KEY_S,
    T = GLFW_KEY_T,
    U = GLFW_KEY_U,
    V = GLFW_KEY_V,
    W = GLFW_KEY_W,
    X = GLFW_KEY_X,
    Y = GLFW_KEY_Y,
    Z = GLFW_KEY_Z,
    LeftBracket = GLFW_KEY_LEFT_BRACKET,
    Backslash = GLFW_KEY_BACKSLASH,
    RightBracket = GLFW_KEY_RIGHT_BRACKET,
    GraveAccent = GLFW_KEY_GRAVE_ACCENT,
    World1 = GLFW_KEY_WORLD_1,
    World2 = GLFW_KEY_WORLD_2,
    Escape = GLFW_KEY_ESCAPE,
    Enter = GLFW_KEY_ENTER,
    Tab = GLFW_KEY_TAB,
    Backspace = GLFW_KEY_BACKSPACE,
    Insert = GLFW_KEY_INSERT,
    Delete = GLFW_KEY_DELETE,
    Right = GLFW_KEY_RIGHT,
    Left = GLFW_KEY_LEFT,
    Down = GLFW_KEY_DOWN,
    Up = GLFW_KEY_UP,
    PageUp = GLFW_KEY_PAGE_UP,
    PageDown = GLFW_KEY_PAGE_DOWN,
    Home = GLFW_KEY_HOME,
    End = GLFW_KEY_END,
    CapsLock = GLFW_KEY_CAPS_LOCK,
    ScrollLock = GLFW_KEY_SCROLL_LOCK,
    NumLock = GLFW_KEY_NUM_LOCK,
    PrintScreen = GLFW_KEY_PRINT_SCREEN,
    Pause = GLFW_KEY_PAUSE,
    F1 = GLFW_KEY_F1,
    F2 = GLFW_KEY_F2,
    F3 = GLFW_KEY_F3,
    F4 = GLFW_KEY_F4,
    F5 = GLFW_KEY_F5,
    F6 = GLFW_KEY_F6,
    F7 = GLFW_KEY_F7,
    F8 = GLFW_KEY_F8,
    F9 = GLFW_KEY_F9,
    F10 = GLFW_KEY_F10,
    F11 = GLFW_KEY_F11,
    F12 = GLFW_KEY_F12,
    F13 = GLFW_KEY_F13,
    F14 = GLFW_KEY_F14,
    F15 = GLFW_KEY_F15,
    F16 = GLFW_KEY_F16,
    F17 = GLFW_KEY_F17,
    F18 = GLFW_KEY_F18,
    F19 = GLFW_KEY_F19,
    F20 = GLFW_KEY_F20,
    F21 = GLFW_KEY_F21,
    F22 = GLFW_KEY_F22,
    F23 = GLFW_KEY_F23,
    F24 = GLFW_KEY_F24,
    F25 = GLFW_KEY_F25,
    Numpad0 = GLFW_KEY_KP_0,
    Numpad1 = GLFW_KEY_KP_1,
    Numpad2 = GLFW_KEY_KP_2,
    Numpad3 = GLFW_KEY_KP_3,
    Numpad4 = GLFW_KEY_KP_4,
    Numpad5 = GLFW_KEY_KP_5,
    Numpad6 = GLFW_KEY_KP_6,
    Numpad7 = GLFW_KEY_KP_7,
    Numpad8 = GLFW_KEY_KP_8,
    Numpad9 = GLFW_KEY_KP_9,
    NumpadDecimal = GLFW_KEY_KP_DECIMAL,
    NumpadDivide = GLFW_KEY_KP_DIVIDE,
    NumpadMultiply = GLFW_KEY_KP_MULTIPLY,
    NumpadSubtract = GLFW_KEY_KP_SUBTRACT,
    NumpadAdd = GLFW_KEY_KP_ADD,
    NumpadEnter = GLFW_KEY_KP_ENTER,
    NumpadEqual = GLFW_KEY_KP_EQUAL,
    LeftShift = GLFW_KEY_LEFT_SHIFT,
    LeftControl = GLFW_KEY_LEFT_CONTROL,
    LeftAlt = GLFW_KEY_LEFT_ALT,
    LeftSuper = GLFW_KEY_LEFT_SUPER,
    RightShift = GLFW_KEY_RIGHT_SHIFT,
    RightControl = GLFW_KEY_RIGHT_CONTROL,
    RightAlt = GLFW_KEY_RIGHT_ALT,
    RightSuper = GLFW_KEY_RIGHT_SUPER,
    Menu = GLFW_KEY_MENU
};

enum class KeyModifier : int {
    Shift = GLFW_MOD_SHIFT,
    Control = GLFW_MOD_CONTROL,
    Alt = GLFW_MOD_ALT,
    Super = GLFW_MOD_SUPER,
    CapsLock = GLFW_MOD_CAPS_LOCK,
    NumLock = GLFW_MOD_NUM_LOCK
};

enum class Action {
    Press = GLFW_PRESS,
    Release = GLFW_RELEASE,
    Repeat = GLFW_REPEAT
};

enum class MouseButton {
    Left = GLFW_MOUSE_BUTTON_LEFT,     // Equivilant to GLFW_MOUSE_BUTTON_1
    Right = GLFW_MOUSE_BUTTON_RIGHT,   // Equivilant to GLFW_MOUSE_BUTTON_2
    Middle = GLFW_MOUSE_BUTTON_MIDDLE, // Equivilant to GLFW_MOUSE_BUTTON_3
    Auxilliary4 = GLFW_MOUSE_BUTTON_4,
    Auxilliary5 = GLFW_MOUSE_BUTTON_5,
    Auxilliary6 = GLFW_MOUSE_BUTTON_6,
    Auxilliary7 = GLFW_MOUSE_BUTTON_7,
    Auxilliary8 = GLFW_MOUSE_BUTTON_8
};

struct WindowPosEvent {
    Math::Vector2i position;
};

struct WindowSizeEvent {
    Math::Vector2i size;
};

struct WindowCloseEvent {};

struct WindowRefreshEvent {};

struct WindowFocusEvent {
    bool focused;
};

struct WindowIconifyEvent {
    bool iconified;
};

struct WindowMaximizeEvent {
    bool maximized;
};

struct FramebufferSizeEvent {
    Math::Vector2i size;
};

struct WindowContentScaleEvent {
    Math::Vector2f scale;
};

struct KeyEvent {
    Key key;
    Action action;
    KeyModifier modifier;
};

struct CharEvent {
    unsigned int codePoint;
};

struct MouseButtonEvent {
    MouseButton button;
    Action action;
};

struct MousePosEvent {
    Math::Vector2d position;
};

struct MouseScrollEvent {
    Math::Vector2d offset;
};

struct DropEvent {
    std::vector<std::string> paths;
};

using Event = std::variant<
    WindowPosEvent,
    WindowSizeEvent,
    WindowCloseEvent,
    WindowRefreshEvent,
    WindowFocusEvent,
    WindowIconifyEvent,
    WindowMaximizeEvent,
    FramebufferSizeEvent,
    WindowContentScaleEvent,
    DropEvent
>;

using MouseEvent = std::variant<
    MouseButtonEvent,
    MousePosEvent,
    MouseScrollEvent
>;

enum class WindowHint : unsigned int {
    Resizable = GLFW_RESIZABLE,
    Visible = GLFW_VISIBLE,
    Decorated = GLFW_DECORATED,
    Focused = GLFW_FOCUSED,
    AutoIconify = GLFW_AUTO_ICONIFY,
    Floating = GLFW_FLOATING,
    Maximized = GLFW_MAXIMIZED,
    CenterCursor = GLFW_CENTER_CURSOR,
    TransparentFramebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,
    FocusOnShow = GLFW_FOCUS_ON_SHOW,
    ScaleToMonitor = GLFW_SCALE_TO_MONITOR,
    ScaleFramebuffer = GLFW_SCALE_FRAMEBUFFER,
    MousePassthrough = GLFW_MOUSE_PASSTHROUGH,
    PositionX = GLFW_POSITION_X,
    PositionY = GLFW_POSITION_Y,
    RedBits = GLFW_RED_BITS,
    GreenBits = GLFW_GREEN_BITS,
    BlueBits = GLFW_BLUE_BITS,
    AlphaBits,
    DepthBits = GLFW_DEPTH_BITS,
    StencilBits = GLFW_STENCIL_BITS,
    AccumRedBits = GLFW_ACCUM_RED_BITS,
    AccumGreenBits = GLFW_ACCUM_GREEN_BITS,
    AccumBlueBits = GLFW_ACCUM_BLUE_BITS,
    AccumAlphaBits = GLFW_ACCUM_ALPHA_BITS,
    AuxBuffers = GLFW_AUX_BUFFERS,
    Stereo = GLFW_STEREO,
    Samples = GLFW_SAMPLES,
    SrgbCapable = GLFW_SRGB_CAPABLE,
    DoubleBuffer = GLFW_DOUBLEBUFFER,
    RefreshRate = GLFW_REFRESH_RATE,
    ClientApi = GLFW_CLIENT_API,
    ContextCreationApi = GLFW_CONTEXT_CREATION_API,
    ContextVersionMajor = GLFW_CONTEXT_VERSION_MAJOR,
    ContextVersionMinor = GLFW_CONTEXT_VERSION_MINOR,
    ContextRobustness = GLFW_CONTEXT_ROBUSTNESS,
    ContextReleaseBehaviour = GLFW_CONTEXT_RELEASE_BEHAVIOR,
    ContextNoError = GLFW_CONTEXT_NO_ERROR,
    OpenGlForwardCompatibility = GLFW_OPENGL_FORWARD_COMPAT,
    OpenGlDebugContext = GLFW_OPENGL_DEBUG_CONTEXT,
    OpenGlProfile = GLFW_OPENGL_PROFILE,
    CocoaRetinaFramebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,
    CocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,
    X11XcbVulkanSurface = GLFW_X11_XCB_VULKAN_SURFACE,
    Win32KeyboardMenu = GLFW_WIN32_KEYBOARD_MENU,
    WaylandLibdecor = GLFW_WAYLAND_LIBDECOR,
    AnyPosition = GLFW_ANY_POSITION
};

enum class WindowHintValue : unsigned int {
    True = GLFW_TRUE,
    False = GLFW_FALSE,
    OpenGlApi = GLFW_OPENGL_API,
    OpenGlEsApi = GLFW_OPENGL_ES_API,
    NoApi = GLFW_NO_API,
    NativeContextApi = GLFW_NATIVE_CONTEXT_API,
    EglContextApi = GLFW_EGL_CONTEXT_API,
    OmesaContextApi = GLFW_OSMESA_CONTEXT_API,
    NoRobustness = GLFW_NO_ROBUSTNESS,
    NoResetNotifiaction = GLFW_NO_RESET_NOTIFICATION,
    LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET,
    AnyReleaseBehaviour = GLFW_ANY_RELEASE_BEHAVIOR,
    ReleaseBehaviourFlush = GLFW_RELEASE_BEHAVIOR_FLUSH,
    ReleaseBehaviourNone = GLFW_RELEASE_BEHAVIOR_NONE,
    OpenGlAnyProfile = GLFW_OPENGL_ANY_PROFILE,
    OpenGlCoreProfile = GLFW_OPENGL_CORE_PROFILE,
    OpenGlCompatibilityProfile = GLFW_OPENGL_COMPAT_PROFILE,
    AnyPosition = GLFW_ANY_POSITION,
    WaylandPreferLibdecor = GLFW_WAYLAND_PREFER_LIBDECOR,
    WaylandDisableLibdecor = GLFW_WAYLAND_DISABLE_LIBDECOR
};

enum class Platform : int {
    Null = GLFW_PLATFORM_NULL,
    Unavailable = GLFW_PLATFORM_UNAVAILABLE,
    Wayland = GLFW_PLATFORM_WAYLAND,
    X11 = GLFW_PLATFORM_X11,
    Win32 = GLFW_PLATFORM_WIN32,
    Cocoa = GLFW_PLATFORM_COCOA
};

using VideoMode = GLFWvidmode;

inline constexpr auto PollEvents = glfwPollEvents;

inline void SetWindowHint(WindowHint hint, WindowHintValue value) noexcept {
    glfwWindowHint(static_cast<int>(hint), static_cast<int>(value));
}

inline void SetWindowHint(WindowHint hint, int value) noexcept {
    glfwWindowHint(static_cast<int>(hint), value);
}

inline void SetWindowHint(int hint, int value) noexcept {
    glfwWindowHint(hint, value);
}

inline Platform GetPlatform() noexcept {
    return static_cast<Platform>(glfwGetPlatform());
}

void* GetDisplay() noexcept {
#ifdef __linux__
    switch (GetPlatform()) {
        case Platform::Wayland:
            return glfwGetWaylandDisplay();
        case Platform::X11:
            return glfwGetX11Display();
        default:
            return nullptr;
    }
#endif
    return nullptr;
}

class Monitor : public ModdersDream::ErrorHandler {
public:
    static Monitor Primary() {
        return Monitor(glfwGetPrimaryMonitor());
    }

    static std::vector<Monitor> GetAll() {
        int count;
        GLFWmonitor** monitors = glfwGetMonitors(&count);

        std::vector<Monitor> result;
        result.reserve(count);

        for (int i = 0; i < count; i++) {
            result.push_back(Monitor(monitors[i]));
        }

        return result;
    }

    inline ModdersDream::ZStringView GetName() const noexcept {
        return glfwGetMonitorName(this->monitor_);
    }

    inline Math::Vector2i GetPosition() const noexcept {
        Math::Vector2i position;
        glfwGetMonitorPos(this->monitor_, &position.x(), &position.y());
        return position;
    }

    void GetWorkArea(Math::Vector2i& position, Math::Vector2i& size) const noexcept {
        Math::Vector2i workPosition;
        Math::Vector2i workSize;
        glfwGetMonitorWorkarea(this->monitor_, &workPosition.x(), &workPosition.y(), &workSize.x(), &workSize.y());
    }

    inline Math::Vector2i GetPhysicalSizeMm() const noexcept {
        Math::Vector2i sizeMm;
        glfwGetMonitorPhysicalSize(this->monitor_, &sizeMm.x(), &sizeMm.y());
        return sizeMm;
    }

    inline Math::Vector2f GetContentScale() const noexcept {
        Math::Vector2f scale;
        glfwGetMonitorContentScale(this->monitor_, &scale.x(), &scale.y());
        return scale;
    }

    inline const VideoMode* GetVideoMode() const noexcept {
        return glfwGetVideoMode(this->monitor_);
    }

    inline const VideoMode* GetVideoModes(int* count) const noexcept {
        return glfwGetVideoModes(this->monitor_, count);
    }

    inline GLFWmonitor* GetNativeHandle() const noexcept {
        return monitor_;
    }

private:
    explicit Monitor(GLFWmonitor* monitor)
        : monitor_(monitor) {
        if (!monitor) {
            const Error error = {
                .system = "Glfw::Monitor",
                .operation = "Monitor construction",
                .description = "Null monitor",
                .code = ModdersDream::ErrorCode::InitializationFailed
            };

            SubmitError(error);
            return;
        }
    }

    GLFWmonitor* monitor_;
};

struct EventConfig {
    bool enableGeneralEvents = true;
    bool enableKeyEvents = true;
    bool enableCharEvents = true;
    bool enableMouseEvents = true;
};

// Forward decleration for Window & Context classes
namespace Callback {

void InitializeError();
void InitializeGlobal();
void InitializeWindow(GLFWwindow* window);

} // namespace Callback

class Window : public ModdersDream::ErrorHandler {
public:
    explicit Window(const Math::Vector2i size, ModdersDream::ZStringView title)
        : Window(size, title, nullptr) {}

    explicit Window(const Math::Vector2i size, ModdersDream::ZStringView title, Monitor monitor)
        : Window(size, title, monitor.GetNativeHandle()) {}

    inline ~Window() noexcept {
        glfwDestroyWindow(this->window_);
    }

    void* GetWindow() const noexcept {
#ifdef _WIN32
        return glfwGetWin32Window(this->window_);
#elifdef __APPLE__
        return glfwGetCocoaView(this->window_);
#elifdef __linux__
        switch (GetPlatform()) {
            case Platform::Wayland:
                return glfwGetWaylandWindow(this->window_);
            case Platform::X11:
                return reinterpret_cast<void*>(static_cast<std::uintptr_t>(glfwGetX11Window(this->window_)));
            default:
                return nullptr;
        }
#endif
        return nullptr;
    }

    inline Math::Vector2i GetFramebufferSize() const noexcept {
        Math::Vector2i size;
        glfwGetFramebufferSize(this->window_, &size.x(), &size.y());
        return size;
    }

    inline void WaitForNonzeroFramebuffer() const noexcept {
        Math::Vector2i size = GetFramebufferSize();
        if (size.x() <= 0 || size.y() <= 0) {
            glfwWaitEvents();
        }
    }

    inline void SetMonitor(Monitor monitor, Math::Vector2i position, Math::Vector2i size, int refreshRate) noexcept {
        glfwSetWindowMonitor(window_, monitor.GetNativeHandle(), position.x(), position.y(), size.x(), size.y(), refreshRate);
    }

    inline void SetMonitor(Monitor monitor, Math::Vector2i position, Math::Vector2i size) noexcept {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor.GetNativeHandle());
        glfwSetWindowMonitor(window_, monitor.GetNativeHandle(), position.x(), position.y(), size.x(), size.y(), mode->refreshRate);
    }

    inline void SetMonitor(std::nullptr_t, Math::Vector2i position, Math::Vector2i size) noexcept {
        glfwSetWindowMonitor(window_, nullptr, position.x(), position.y(), size.x(), size.y(), 0);
    }

    inline void SetMonitor(Math::Vector2i position, Math::Vector2i size) noexcept {
        glfwSetWindowMonitor(window_, nullptr, position.x(), position.y(), size.x(), size.y(), 0);
    }

    inline void SetMonitorFullscreen(Monitor monitor) noexcept {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor.GetNativeHandle());
        glfwSetWindowMonitor(window_, monitor.GetNativeHandle(), 0, 0, mode->width, mode->height, mode->refreshRate);
    }

    inline void SetWindowedToCenterOfMonitor(Monitor monitor, Math::Vector2i size) noexcept {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor.GetNativeHandle());
        int posx = mode->width / 2 - size.x() / 2;
        int posy = mode->height / 2 - size.y() / 2;
        glfwSetWindowMonitor(window_, nullptr, posx, posy, size.x(), size.y(), mode->refreshRate);
    }

    inline bool ShouldClose() const noexcept {
        return glfwWindowShouldClose(this->window_);
    }

    inline const GLFWwindow* GetHandle() const noexcept {
        return this->window_;
    }

    static Window* GetRegisteredWindow(GLFWwindow* handle) {
        return windows_[handle];
    }

    inline const std::vector<Event>& GeneralEvents() const noexcept {
        return generalEvents_;
    }

    inline const std::vector<KeyEvent>& KeyEvents() const noexcept {
        return keyEvents_;
    }

    inline const std::vector<CharEvent>& CharEvents() const noexcept {
        return charEvents_;
    }

    inline const std::vector<MouseEvent>& MouseEvents() const noexcept {
        return mouseEvents_;
    }

    inline void AddGeneralEvent(const Event& event) {
        generalEvents_.push_back(event);
    }

    inline void AddKeyEvent(const KeyEvent& event) {
        keyEvents_.push_back(event);
    }

    inline void AddCharEvent(const CharEvent& event) {
        charEvents_.push_back(event);
    }

    inline void AddMouseEvent(const MouseEvent& event) {
        mouseEvents_.push_back(event);
    }

    void ClearEvents() noexcept {
        generalEvents_.clear();
        keyEvents_.clear();
        charEvents_.clear();
        mouseEvents_.clear();
    }

private:
    explicit Window(const Math::Vector2i size, ModdersDream::ZStringView title, GLFWmonitor* monitor) {
        this->window_ = glfwCreateWindow(size.x(), size.y(), title, monitor, nullptr);

        if (!this->window_) {
            const ModdersDream::Error error{
                .system = "Glfw::Window",
                .operation = "glfwCreateWindow",
                .description = "Failed to initialize window",
                .code = ModdersDream::ErrorCode::InitializationFailed
            };
            SubmitError(error);
            return;
        }

        this->windows_[window_] = this;
        Callback::InitializeWindow(this->window_);
    }

    GLFWwindow* window_;

    std::vector<Event> generalEvents_;
    std::vector<KeyEvent> keyEvents_;
    std::vector<CharEvent> charEvents_;
    std::vector<MouseEvent> mouseEvents_;

    inline static std::unordered_map<GLFWwindow*, Window*> windows_;
};

class Context : public ModdersDream::ErrorHandler {
public:
    Context() {
        Callback::InitializeError();
        if (!glfwInit()) {
            const Error error = {
                .system = "Glfw::Context",
                .operation = "glfwInit",
                .description = "Failed to initialize GLFW",
                .code = ModdersDream::ErrorCode::InitializationFailed
            };
            ErrorHandler::SubmitError(error);
            return;
        }
        Callback::InitializeGlobal();
    }

    ~Context() noexcept {
        glfwTerminate();
    }
};

std::vector<Event> globalEvents;

namespace Callback {

inline void AddGlobalEvent(const Event& event) {
    globalEvents.push_back(event);
};

inline void AddGeneralEvent(GLFWwindow* window, const Event& event) {
    Window::GetRegisteredWindow(window)->AddGeneralEvent(event);
}

inline void AddKeyEvent(GLFWwindow* window, const KeyEvent& event) {
    Window::GetRegisteredWindow(window)->AddKeyEvent(event);
}

inline void AddCharEvent(GLFWwindow* window, const CharEvent& event) {
    Window::GetRegisteredWindow(window)->AddCharEvent(event);
}

inline void AddMouseEvent(GLFWwindow* window, const MouseEvent& event) {
    Window::GetRegisteredWindow(window)->AddMouseEvent(event);
}

//
// Window callbacks
//

void WindowPos(GLFWwindow* window, int xPos, int yPos) {
    const Event event = WindowPosEvent({xPos, yPos});
    AddGeneralEvent(window, event);
}

void WindowSize(GLFWwindow* window, int xSize, int ySize) {
    const Event event = WindowSizeEvent({xSize, ySize});
    AddGeneralEvent(window, event);
}

void WindowClose(GLFWwindow* window) {
    const Event event = WindowCloseEvent();
    AddGeneralEvent(window, event);
}

void WindowRefresh(GLFWwindow* window) {
    const Event event = WindowRefreshEvent();
    AddGeneralEvent(window, event);
}

void WindowFocus(GLFWwindow* window, int focused) {
    const Event event = WindowFocusEvent(focused);
    AddGeneralEvent(window, event);
}

void WindowIconify(GLFWwindow* window, int iconified) {
    const Event event = WindowIconifyEvent(iconified);
    AddGeneralEvent(window, event);
}

void WindowMaximize(GLFWwindow* window, int maximized) {
    const Event event = WindowMaximizeEvent(maximized);
    AddGeneralEvent(window, event);
}

void FramebufferSize(GLFWwindow* window, int xSize, int ySize) {
    const Event event = FramebufferSizeEvent({xSize, ySize});
    AddGeneralEvent(window, event);
}

void WindowContentScale(GLFWwindow* window, float xScale, float yScale) {
    const Event event = WindowContentScaleEvent({xScale, yScale});
    AddGeneralEvent(window, event);
}

//
// Input callbacks
//

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
    const KeyEvent event(static_cast<Key>(key), static_cast<Action>(action), static_cast<KeyModifier>(mods));
    AddKeyEvent(window, event);
}

void Character(GLFWwindow* window, unsigned int codePoint) {
    const CharEvent event(codePoint);
    AddCharEvent(window, event);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    const MouseEvent event = MouseButtonEvent(static_cast<MouseButton>(button), static_cast<Action>(action));
    AddMouseEvent(window, event);
}

void CursorPos(GLFWwindow* window, double xPos, double yPos) {
    const MouseEvent event = MousePosEvent({xPos, yPos});
    AddMouseEvent(window, event);
}

void Scroll(GLFWwindow* window, double xOffset, double yOffset) {
    const MouseEvent event = MouseScrollEvent({xOffset, yOffset});
    AddMouseEvent(window, event);
}

void Drop(GLFWwindow* window, int count, const char** paths) {
    DropEvent drop;

    for (int i = 0; i < count; ++i) {
        drop.paths.emplace_back(paths[i]);
    }

    const Event event = drop;
    AddGeneralEvent(window, event);
}

// TODO: Joystick and monitor events & handle globalEvents vector
void Joystick(int jid, int event) {
}

void Monitor(GLFWmonitor* monitor, int event) {
}

void ErrorCallback(int errorCode, const char* description) {
    logger.Log(ModdersDream::LogLevel::Error, "{}: {}", errorCode, description);
}

// Context class calls it automatically
// Nothing would (probably) happen if you call it twice
void InitializeError() {
    glfwSetErrorCallback(ErrorCallback);
}

// Context class calls it automatically
// Nothing would (probably) happen if you call it twice
void InitializeGlobal() {
    glfwSetJoystickCallback(Joystick);
    glfwSetMonitorCallback(Monitor);
}

// Window class calls it automatically
// Nothing would (probably) happen if you call it twice
void InitializeWindow(GLFWwindow* window) {
    glfwSetWindowPosCallback(window, WindowPos);
    glfwSetWindowSizeCallback(window, WindowSize);
    glfwSetWindowCloseCallback(window, WindowClose);
    glfwSetWindowRefreshCallback(window, WindowRefresh);
    glfwSetWindowFocusCallback(window, WindowFocus);
    glfwSetWindowIconifyCallback(window, WindowIconify);
    glfwSetWindowMaximizeCallback(window, WindowMaximize);
    glfwSetFramebufferSizeCallback(window, FramebufferSize);
    glfwSetWindowContentScaleCallback(window, WindowContentScale);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCharCallback(window, Character);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPos);
    glfwSetScrollCallback(window, Scroll);
    glfwSetDropCallback(window, Drop);
}

} // namespace Callback

} // namespace ModdersDream::Glfw

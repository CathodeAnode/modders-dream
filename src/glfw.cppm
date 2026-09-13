module;
#include <GLFW/glfw3.h>
export module md.glfw;

import md.logger;
import md.error;
import md.zstring_view;

import std;

namespace {

md::Logger logger("GLFW");

} // namespace

export namespace md::glfw {

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
    Button4 = GLFW_MOUSE_BUTTON_4,
    Button5 = GLFW_MOUSE_BUTTON_5,
    Button6 = GLFW_MOUSE_BUTTON_6,
    Button7 = GLFW_MOUSE_BUTTON_7,
    Button8 = GLFW_MOUSE_BUTTON_8
};

struct WindowPosEvent {
    int x, y;
};

struct WindowSizeEvent {
    int x, y;
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
    int x, y;
};

struct WindowContentScaleEvent {
    float x, y;
};

struct KeyEvent {
    Key key;
    Action action;
    KeyModifier modifier;
};

struct CharEvent {
    unsigned int codepoint;
};

struct MouseButtonEvent {
    MouseButton button;
    Action action;
};

struct MousePosEvent {
    double x, y;
};

struct MouseScrollEvent {
    double xoffset, yoffset;
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
    AlphaBitsGLFW_ALPHA_BITS,
    DepthBits = GLFW_DEPTH_BITS,
    StencilBits = GLFW_STENCIL_BITS,
    AccumRedBits = GLFW_ACCUM_RED_BITS,
    AccumGreenBits = GLFW_ACCUM_GREEN_BITS,
    ACcumBlueBits = GLFW_ACCUM_BLUE_BITS,
    AccumAlphaBits = GLFW_ACCUM_ALPHA_BITS,
    AuxBuffers = GLFW_AUX_BUFFERS,
    Stereo = GLFW_STEREO,
    Samples = GLFW_SAMPLES,
    SRGBCapable = GLFW_SRGB_CAPABLE,
    DoubleBuffer = GLFW_DOUBLEBUFFER,
    RefreshRate = GLFW_REFRESH_RATE,
    ClientAPI = GLFW_CLIENT_API,
    ContextCreationAPI = GLFW_CONTEXT_CREATION_API,
    ContextVersionMajor = GLFW_CONTEXT_VERSION_MAJOR,
    ContextVersionMinor = GLFW_CONTEXT_VERSION_MINOR,
    ContextRobustness = GLFW_CONTEXT_ROBUSTNESS,
    ContextReleaseBehaviour = GLFW_CONTEXT_RELEASE_BEHAVIOR,
    ContextNoError = GLFW_CONTEXT_NO_ERROR,
    OpenGLForwardCompatibility = GLFW_OPENGL_FORWARD_COMPAT,
    OpenGLDebugContext = GLFW_OPENGL_DEBUG_CONTEXT,
    OpenGLProfile = GLFW_OPENGL_PROFILE,
    CocoaRetinaFramebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,
    CocoaGraphicsSwitching = GLFW_COCOA_GRAPHICS_SWITCHING,
    X11XCBVulkanSurface = GLFW_X11_XCB_VULKAN_SURFACE,
    Win32KeyboardMenu = GLFW_WIN32_KEYBOARD_MENU,
    WaylandLibdecor = GLFW_WAYLAND_LIBDECOR,
    AnyPosition = GLFW_ANY_POSITION
};

enum class WindowHintValue : unsigned int {
    True = GLFW_TRUE,
    False = GLFW_FALSE,
    OpenGLAPI = GLFW_OPENGL_API,
    OpenGLESAPI = GLFW_OPENGL_ES_API,
    NoAPI = GLFW_NO_API,
    NativeContextAPI = GLFW_NATIVE_CONTEXT_API,
    EGLContextAPI = GLFW_EGL_CONTEXT_API,
    OmesaContextAPI = GLFW_OSMESA_CONTEXT_API,
    NoRobustness = GLFW_NO_ROBUSTNESS,
    NoResetNotifiaction = GLFW_NO_RESET_NOTIFICATION,
    LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET,
    AnyReleaseBehaviour = GLFW_ANY_RELEASE_BEHAVIOR,
    ReleaseBehaviourFlush = GLFW_RELEASE_BEHAVIOR_FLUSH,
    ReleaseBehaviourNone = GLFW_RELEASE_BEHAVIOR_NONE,
    OpenGLAnyProfile = GLFW_OPENGL_ANY_PROFILE,
    OpenGLCoreProfile = GLFW_OPENGL_CORE_PROFILE,
    OpenGLCompatibilityProfile = GLFW_OPENGL_COMPAT_PROFILE,
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

inline constexpr auto poll_events = glfwPollEvents;

inline constexpr void window_hint(WindowHint hint, WindowHintValue value) {
    glfwWindowHint(static_cast<int>(hint), static_cast<int>(value));
}

inline constexpr void window_hint(WindowHint hint, int value) {
    glfwWindowHint(static_cast<int>(hint), value);
}

inline constexpr void window_hint(int hint, int value) {
    glfwWindowHint(hint, value);
}

inline constexpr Platform get_platform() {
    return static_cast<Platform>(glfwGetPlatform());
}

class Monitor {
public:
    md::zstring_view get_name() {
        return glfwGetMonitorName(this->monitor);
    }

    inline void get_position(int* xpos, int* ypos) {
        glfwGetMonitorPos(this->monitor, xpos, ypos);
    }

    inline void get_work_area(int* xpos, int* ypos, int* width, int* height) {
        glfwGetMonitorWorkarea(this->monitor, xpos, ypos, width, height);
    }

    inline void get_physical_size(int* widthMM, int* heightMM) {
        glfwGetMonitorPhysicalSize(this->monitor, widthMM, heightMM);
    }

    inline void get_content_scale(float* xscale, float* yscale) {
        glfwGetMonitorContentScale(this->monitor, xscale, yscale);
    }

    inline const VideoMode* get_video_mode() {
        return glfwGetVideoMode(this->monitor);
    }

    inline const VideoMode* get_video_modes(int* count) {
        return glfwGetVideoModes(this->monitor, count);
    }

    inline GLFWmonitor* get_native_handle() {
        return monitor;
    }

private:
    GLFWmonitor* monitor;
};

struct EventConfig {
    bool enable_general_events = true;
    bool enable_key_events = true;
    bool enable_char_events = true;
    bool enable_mouse_events = true;
};

// Forward decleration for Window & Context classes
namespace callback {

void initialize_error();
void initialize_global();
void initialize_window(GLFWwindow* window);

} // namespace callback

class Window : public md::ErrorHandler {
public:
    inline Window(int width, int height, md::zstring_view title) {
        this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!this->window) {
            md::Error error{
                .system = "Window",
                .operation = "glfwCreateWindow",
                .description = "Failed to initialize window",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }

        this->windows[window] = this;
        callback::initialize_window(this->window);
    }

    inline Window(int width, int height, md::zstring_view title, Monitor monitor) {
        this->window = glfwCreateWindow(width, height, title, monitor.get_native_handle(), nullptr);

        if (!this->window) {
            md::Error error{
                .system = "Window",
                .operation = "glfwCreateWindow",
                .description = "Failed to initialize window",
                .code = md::ErrorCode::InitializationFailed
            };
            submit_error(error);
            return;
        }

        this->windows[window] = this;
        callback::initialize_window(this->window);
    }

    inline ~Window() {
        glfwDestroyWindow(this->window);
    }

    inline bool should_close() const {
        return glfwWindowShouldClose(this->window);
    }

    inline const GLFWwindow* get_handle() const {
        return this->window;
    }

    inline static Window* get_registered_window(GLFWwindow* handle) {
        return windows[handle];
    }

    inline const std::vector<Event>& general_events() {
        return general_events_;
    }

    inline const std::vector<KeyEvent>& key_events() {
        return key_events_;
    }

    inline const std::vector<CharEvent>& char_events() {
        return char_events_;
    }

    inline const std::vector<MouseEvent>& mouse_events() {
        return mouse_events_;
    }

    inline void add_general_event(Event& event) {
        general_events_.push_back(event);
    }

    inline void add_key_event(KeyEvent& event) {
        key_events_.push_back(event);
    }

    inline void add_char_event(CharEvent& event) {
        char_events_.push_back(event);
    }

    inline void add_mouse_event(MouseEvent& event) {
        mouse_events_.push_back(event);
    }

    void clear_events() {
        general_events_.clear();
        key_events_.clear();
        char_events_.clear();
        mouse_events_.clear();
    }

private:
    GLFWwindow* window;

    std::vector<Event> general_events_;
    std::vector<KeyEvent> key_events_;
    std::vector<CharEvent> char_events_;
    std::vector<MouseEvent> mouse_events_;

    inline static std::unordered_map<GLFWwindow*, Window*> windows;
};

class Context : public md::ErrorHandler {
public:
    Context() {
        callback::initialize_error();
        if (!glfwInit()) {
            Error error = {
                .system = "Context",
                .operation = "glfwInit",
                .description = "Failed to initialize GLFW",
                .code = md::ErrorCode::InitializationFailed
            };
            ErrorHandler::submit_error(error);
            return;
        }
        callback::initialize_global();
    }

    ~Context() {
        glfwTerminate();
    }
};

std::vector<Event> global_events;

namespace callback {

inline void add_global_event(Event& event) {
    global_events.push_back(event);
};

inline void add_general_event(GLFWwindow* window, Event& event) {
    Window::get_registered_window(window)->add_general_event(event);
}

inline void add_key_event(GLFWwindow* window, KeyEvent& event) {
    Window::get_registered_window(window)->add_key_event(event);
}

inline void add_char_event(GLFWwindow* window, CharEvent& event) {
    Window::get_registered_window(window)->add_char_event(event);
}

inline void add_mouse_event(GLFWwindow* window, MouseEvent& event) {
    Window::get_registered_window(window)->add_mouse_event(event);
}

//
// Window callbacks
//

void window_pos(GLFWwindow* window, int xpos, int ypos) {
    Event event = WindowPosEvent(xpos, ypos);
    add_general_event(window, event);
}

void window_size(GLFWwindow* window, int xsize, int ysize) {
    Event event = WindowSizeEvent(xsize, ysize);
    add_general_event(window, event);
}

void window_close(GLFWwindow* window) {
    Event event = WindowCloseEvent();
    add_general_event(window, event);
}

void window_refresh(GLFWwindow* window) {
    Event event = WindowRefreshEvent();
    add_general_event(window, event);
}

void window_focus(GLFWwindow* window, int focused) {
    Event event = WindowFocusEvent(focused);
    add_general_event(window, event);
}

void window_iconify(GLFWwindow* window, int iconified) {
    Event event = WindowIconifyEvent(iconified);
    add_general_event(window, event);
}

void window_maximize(GLFWwindow* window, int maximized) {
    Event event = WindowMaximizeEvent(maximized);
    add_general_event(window, event);
}

void framebuffer_size(GLFWwindow* window, int xsize, int ysize) {
    Event event = FramebufferSizeEvent(xsize, ysize);
    add_general_event(window, event);
}

void window_content_scale(GLFWwindow* window, float xscale, float yscale) {
    Event event = WindowContentScaleEvent(xscale, yscale);
    add_general_event(window, event);
}

//
// Input callbacks
//

void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    KeyEvent event(static_cast<Key>(key), static_cast<Action>(action), static_cast<KeyModifier>(mods));
    add_key_event(window, event);
}

void character(GLFWwindow* window, unsigned int codepoint) {
    CharEvent event(codepoint);
    add_char_event(window, event);
}

void mouse_button(GLFWwindow* window, int button, int action, int mods) {
    MouseEvent event = MouseButtonEvent(static_cast<MouseButton>(button), static_cast<Action>(action));
    add_mouse_event(window, event);
}

void cursor_pos(GLFWwindow* window, double xpos, double ypos) {
    MouseEvent event = MousePosEvent(xpos, ypos);
    add_mouse_event(window, event);
}

void scroll(GLFWwindow* window, double xoffset, double yoffset) {
    MouseEvent event = MouseScrollEvent(xoffset, yoffset);
    add_mouse_event(window, event);
}

void drop(GLFWwindow* window, int count, const char** paths) {
    DropEvent drop;

    for (int i = 0; i < count; ++i) {
        drop.paths.emplace_back(paths[i]);
    }

    Event event = drop;
    add_general_event(window, event);
}

// TODO: Joystick and monitor events & handle global_events vector
void joystick(int jid, int event) {
}

void monitor(GLFWmonitor* monitor, int event) {
}

void error(int error_code, const char* description) {
    logger.log(md::LogLevel::Error, "{}: {}", error_code, description);
}

// Context class calls it automatically
// Nothing would (probably) happen if you call it twice
void initialize_error() {
    glfwSetErrorCallback(error);
}

// Context class calls it automatically
// Nothing would (probably) happen if you call it twice
void initialize_global() {
    glfwSetJoystickCallback(joystick);
    glfwSetMonitorCallback(monitor);
}

// Window class calls it automatically
// Nothing would (probably) happen if you call it twice
void initialize_window(GLFWwindow* window) {
    glfwSetWindowPosCallback(window, window_pos);
    glfwSetWindowSizeCallback(window, window_size);
    glfwSetWindowCloseCallback(window, window_close);
    glfwSetWindowRefreshCallback(window, window_refresh);
    glfwSetWindowFocusCallback(window, window_focus);
    glfwSetWindowIconifyCallback(window, window_iconify);
    glfwSetWindowMaximizeCallback(window, window_maximize);
    glfwSetFramebufferSizeCallback(window, framebuffer_size);
    glfwSetWindowContentScaleCallback(window, window_content_scale);

    glfwSetKeyCallback(window, key);
    glfwSetCharCallback(window, character);
    glfwSetMouseButtonCallback(window, mouse_button);
    glfwSetCursorPosCallback(window, cursor_pos);
    glfwSetScrollCallback(window, scroll);
    glfwSetDropCallback(window, drop);
}

} // namespace callback

} // namespace md::glfw

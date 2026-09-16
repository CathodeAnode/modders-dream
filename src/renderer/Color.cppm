export module ModdersDream.Renderer.Color;

import ModdersDream.Math;

namespace ModdersDream::Renderer {

struct ColorRgb : Math::Vector3f {
    using Math::Vector3f::Vector3f;

    constexpr float& R() { return x(); }
    constexpr float& G() { return y(); }
    constexpr float& B() { return z(); }

    const float& R() const { return x(); }
    const float& G() const { return y(); }
    const float& B() const { return z(); }
};

struct ColorRgba : Math::Vector4f {
    using Math::Vector4f::Vector4f;

    constexpr float& R() { return x(); }
    constexpr float& G() { return y(); }
    constexpr float& B() { return z(); }
    constexpr float& A() { return w(); }

    const float& R() const { return x(); }
    const float& G() const { return y(); }
    const float& B() const { return z(); }
    const float& A() const { return w(); }
};

} // namespace ModdersDream::Renderer

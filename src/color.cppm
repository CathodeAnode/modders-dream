export module md.renderer.color;

import md.math;

namespace md::renderer {

struct ColorRGB : math::Vector3f {
    using math::Vector3f::Vector3f;

    constexpr float& r() { return x(); }
    constexpr float& g() { return y(); }
    constexpr float& b() { return z(); }

    const float& r() const { return x(); }
    const float& g() const { return y(); }
    const float& b() const { return z(); }
};

struct ColorRGBA : math::Vector4f {
    using math::Vector4f::Vector4f;

    constexpr float& r() { return x(); }
    constexpr float& g() { return y(); }
    constexpr float& b() { return z(); }
    constexpr float& a() { return w(); }

    const float& r() const { return x(); }
    const float& g() const { return y(); }
    const float& b() const { return z(); }
    const float& a() const { return w(); }
};

} // namespace md::renderer

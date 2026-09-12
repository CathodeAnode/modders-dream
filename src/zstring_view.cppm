export module md.zstring_view;

import std;

export namespace md {

class zstring_view {
public:
    template <std::size_t N>
    constexpr zstring_view(const char (&arr)[N]) noexcept : data_(arr), size_(N - 1) {}

    constexpr zstring_view(std::nullptr_t) noexcept : data_(nullptr), size_(0) {}

    constexpr zstring_view(const char* data) noexcept : data_(data), size_(std::strlen(data)) {}

    constexpr operator const char*() const noexcept {
        return data_;
    }

    constexpr const char* c_str() const noexcept {
        return data_;
    }

    constexpr const char* data() const noexcept {
        return data_;
    }

    constexpr std::size_t size() const noexcept {
        return size_;
    }

    constexpr bool empty() const noexcept {
        return size_ == 0;
    }

    constexpr explicit operator bool() const noexcept {
        return data_ != nullptr;
    }

private:
    const char* data_;
    const std::size_t size_;
};

} // namespace md

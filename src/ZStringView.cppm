export module ModdersDream.ZStringView;

import std;

export namespace ModdersDream {

class ZStringView {
public:
    template <std::size_t N>
    constexpr ZStringView(const char (&arr)[N]) noexcept : data_(arr), size_(N - 1) {}

    constexpr ZStringView(std::nullptr_t) noexcept : data_(nullptr), size_(0) {}

    constexpr ZStringView(const char* data) noexcept : data_(data), size_(std::strlen(data)) {}

    constexpr operator const char*() const noexcept {
        return data_;
    }

    constexpr const char* CStr() const noexcept {
        return data_;
    }

    constexpr const char* Data() const noexcept {
        return data_;
    }

    constexpr std::size_t Size() const noexcept {
        return size_;
    }

    constexpr bool Empty() const noexcept {
        return size_ == 0;
    }

    constexpr explicit operator bool() const noexcept {
        return data_ != nullptr;
    }

private:
    const char* data_;
    const std::size_t size_;
};

} // namespace ModdersDream

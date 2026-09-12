export module md.fixed_string;

import std;

export namespace md {

template <std::size_t N>
class fixed_string {
public:
    constexpr fixed_string(const char (&str)[N]) {
        std::copy_n(str, N, data_);
    }

    constexpr operator std::string_view() const {
        return {data_, N - 1};
    }

    constexpr char* data() {
        return data;
    }

    constexpr std::size_t size() const {
        return N;
    }

private:
    char data_[N];
};

} // namespace md

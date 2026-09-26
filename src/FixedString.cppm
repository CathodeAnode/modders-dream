export module ModdersDream.FixedString;

import std;

export namespace ModdersDream {

template <typename CharT, std::size_t N, typename Traits = std::char_traits<CharT>>
struct FixedString {
    using storage_type = std::array<CharT, N + 1>;
    using traits_type = Traits;
    using value_type = CharT;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename storage_type::iterator;
    using const_iterator = typename storage_type::const_iterator;
    using reverse_iterator = typename storage_type::reverse_iterator;
    using const_reverse_iterator = typename storage_type::const_reverse_iterator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using string_view_type = std::basic_string_view<value_type, traits_type>;

    static constexpr auto npos = string_view_type::npos;

    storage_type _data{};

    constexpr FixedString() noexcept = default;

    constexpr FixedString(const value_type (&array)[N + 1]) noexcept {
        for (size_type i = 0; i < N + 1; ++i)
            _data[i] = array[i];
    }

    constexpr FixedString& operator=(const value_type (&array)[N + 1]) noexcept {
        for (size_type i = 0; i < N + 1; ++i)
            _data[i] = array[i];
        return *this;
    }

    [[nodiscard]] constexpr iterator begin() noexcept { return _data.begin(); }
    [[nodiscard]] constexpr const_iterator begin() const noexcept { return _data.begin(); }
    [[nodiscard]] constexpr iterator end() noexcept { return _data.end() - 1; }
    [[nodiscard]] constexpr const_iterator end() const noexcept { return _data.end() - 1; }
    [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return _data.cbegin(); }
    [[nodiscard]] constexpr const_iterator cend() const noexcept { return _data.cend() - 1; }
    [[nodiscard]] constexpr reverse_iterator rbegin() noexcept { return _data.rbegin() + 1; }
    [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return _data.rbegin() + 1; }
    [[nodiscard]] constexpr reverse_iterator rend() noexcept { return _data.rend(); }
    [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return _data.rend(); }
    [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return _data.crbegin() + 1; }
    [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return _data.crend(); }

    [[nodiscard]] constexpr size_type size() const noexcept { return N; }
    [[nodiscard]] constexpr size_type length() const noexcept { return N; }
    [[nodiscard]] constexpr size_type max_size() const noexcept { return N; }
    [[nodiscard]] constexpr bool empty() const noexcept { return N == 0; }

    [[nodiscard]] constexpr reference operator[](size_type n) { return _data[n]; }
    [[nodiscard]] constexpr const_reference operator[](size_type n) const { return _data[n]; }
    [[nodiscard]] constexpr reference at(size_type n) { return _data.at(n); }
    [[nodiscard]] constexpr const_reference at(size_type n) const { return _data.at(n); }

    [[nodiscard]] constexpr reference front() noexcept
        requires(N > 0)
    { return _data.front(); }
    [[nodiscard]] constexpr const_reference front() const noexcept
        requires(N > 0)
    { return _data.front(); }
    [[nodiscard]] constexpr reference back() noexcept
        requires(N > 0)
    { return _data[N - 1]; }
    [[nodiscard]] constexpr const_reference back() const noexcept
        requires(N > 0)
    { return _data[N - 1]; }

    [[nodiscard]] constexpr pointer data() noexcept { return _data.data(); }
    [[nodiscard]] constexpr const_pointer data() const noexcept { return _data.data(); }
    [[nodiscard]] constexpr const_pointer c_str() const noexcept { return _data.data(); }

    [[nodiscard]] constexpr operator string_view_type() const noexcept { return {data(), N}; }
    [[nodiscard]] constexpr string_view_type view() const noexcept { return *this; }

    template <size_type pos = 0, size_type count = npos>
        requires(pos <= N)
    [[nodiscard]] constexpr auto substr() const noexcept {
        constexpr size_type result_size =
            (pos >= N) ? 0 : (count < N - pos ? count : N - pos);
        FixedString<CharT, result_size, Traits> result{};
        for (size_type i = 0; i < result_size; ++i)
            result[i] = _data[pos + i];
        return result;
    }

    [[nodiscard]] constexpr size_type find(string_view_type sv, size_type pos = 0) const noexcept { return view().find(sv, pos); }
    [[nodiscard]] constexpr size_type find(const value_type* s, size_type pos, size_type n) const { return view().find(s, pos, n); }
    [[nodiscard]] constexpr size_type find(const value_type* s, size_type pos = 0) const { return view().find(s, pos); }
    [[nodiscard]] constexpr size_type find(value_type c, size_type pos = 0) const noexcept { return view().find(c, pos); }

    [[nodiscard]] constexpr size_type rfind(string_view_type sv, size_type pos = npos) const noexcept { return view().rfind(sv, pos); }
    [[nodiscard]] constexpr size_type rfind(const value_type* s, size_type pos, size_type n) const { return view().rfind(s, pos, n); }
    [[nodiscard]] constexpr size_type rfind(const value_type* s, size_type pos = npos) const { return view().rfind(s, pos); }
    [[nodiscard]] constexpr size_type rfind(value_type c, size_type pos = npos) const noexcept { return view().rfind(c, pos); }

    [[nodiscard]] constexpr size_type find_first_of(string_view_type sv, size_type pos = 0) const noexcept { return view().find_first_of(sv, pos); }
    [[nodiscard]] constexpr size_type find_first_of(const value_type* s, size_type pos, size_type n) const { return view().find_first_of(s, pos, n); }
    [[nodiscard]] constexpr size_type find_first_of(const value_type* s, size_type pos = 0) const { return view().find_first_of(s, pos); }
    [[nodiscard]] constexpr size_type find_first_of(value_type c, size_type pos = 0) const noexcept { return view().find_first_of(c, pos); }

    [[nodiscard]] constexpr size_type find_last_of(string_view_type sv, size_type pos = npos) const noexcept { return view().find_last_of(sv, pos); }
    [[nodiscard]] constexpr size_type find_last_of(const value_type* s, size_type pos, size_type n) const { return view().find_last_of(s, pos, n); }
    [[nodiscard]] constexpr size_type find_last_of(const value_type* s, size_type pos = npos) const { return view().find_last_of(s, pos); }
    [[nodiscard]] constexpr size_type find_last_of(value_type c, size_type pos = npos) const noexcept { return view().find_last_of(c, pos); }

    [[nodiscard]] constexpr size_type find_first_not_of(string_view_type sv, size_type pos = 0) const noexcept { return view().find_first_not_of(sv, pos); }
    [[nodiscard]] constexpr size_type find_first_not_of(const value_type* s, size_type pos, size_type n) const { return view().find_first_not_of(s, pos, n); }
    [[nodiscard]] constexpr size_type find_first_not_of(const value_type* s, size_type pos = 0) const { return view().find_first_not_of(s, pos); }
    [[nodiscard]] constexpr size_type find_first_not_of(value_type c, size_type pos = 0) const noexcept { return view().find_first_not_of(c, pos); }

    [[nodiscard]] constexpr size_type find_last_not_of(string_view_type sv, size_type pos = npos) const noexcept { return view().find_last_not_of(sv, pos); }
    [[nodiscard]] constexpr size_type find_last_not_of(const value_type* s, size_type pos, size_type n) const { return view().find_last_not_of(s, pos, n); }
    [[nodiscard]] constexpr size_type find_last_not_of(const value_type* s, size_type pos = npos) const { return view().find_last_not_of(s, pos); }
    [[nodiscard]] constexpr size_type find_last_not_of(value_type c, size_type pos = npos) const noexcept { return view().find_last_not_of(c, pos); }

    [[nodiscard]] constexpr int compare(string_view_type v) const noexcept { return view().compare(v); }
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, string_view_type v) const {
        return view().compare(pos1, count1, v);
    }
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, string_view_type v, size_type pos2, size_type count2) const {
        return view().compare(pos1, count1, v, pos2, count2);
    }
    [[nodiscard]] constexpr int compare(const value_type* s) const { return view().compare(s); }
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, const value_type* s) const {
        return view().compare(pos1, count1, s);
    }
    [[nodiscard]] constexpr int compare(size_type pos1, size_type count1, const value_type* s, size_type count2) const {
        return view().compare(pos1, count1, s, count2);
    }

    [[nodiscard]] constexpr bool starts_with(string_view_type v) const noexcept { return view().starts_with(v); }
    [[nodiscard]] constexpr bool starts_with(value_type c) const noexcept { return view().starts_with(c); }
    [[nodiscard]] constexpr bool starts_with(const value_type* s) const { return view().starts_with(s); }

    [[nodiscard]] constexpr bool ends_with(string_view_type v) const noexcept { return view().ends_with(v); }
    [[nodiscard]] constexpr bool ends_with(value_type c) const noexcept { return view().ends_with(c); }
    [[nodiscard]] constexpr bool ends_with(const value_type* s) const { return view().ends_with(s); }

    [[nodiscard]] constexpr bool contains(string_view_type v) const noexcept { return view().contains(v); }
    [[nodiscard]] constexpr bool contains(value_type c) const noexcept { return view().contains(c); }
    [[nodiscard]] constexpr bool contains(const value_type* s) const { return view().contains(s); }

    constexpr void swap(FixedString& other) noexcept(std::is_nothrow_swappable_v<storage_type>) {
        _data.swap(other._data);
    }
};

template <typename CharT, typename Traits, std::size_t N1, std::size_t N2>
[[nodiscard]] constexpr auto operator<=>(const FixedString<CharT, N1, Traits>& lhs, const FixedString<CharT, N2, Traits>& rhs) {
    return static_cast<std::basic_string_view<CharT, Traits>>(lhs) <=> rhs;
}

template <typename CharT, typename Traits, std::size_t N1, std::size_t N2>
[[nodiscard]] constexpr bool operator==(const FixedString<CharT, N1, Traits>& lhs, const FixedString<CharT, N2, Traits>& rhs) {
    return static_cast<std::basic_string_view<CharT, Traits>>(lhs) == rhs;
}

template <typename CharT, typename Traits, std::size_t N>
[[nodiscard]] constexpr auto operator<=>(const FixedString<CharT, N, Traits>& lhs, std::basic_string_view<CharT, Traits> rhs) {
    return static_cast<std::basic_string_view<CharT, Traits>>(lhs) <=> rhs;
}

template <typename CharT, typename Traits, std::size_t N>
[[nodiscard]] constexpr auto operator<=>(std::basic_string_view<CharT, Traits> lhs, const FixedString<CharT, N, Traits>& rhs) {
    return lhs <=> static_cast<std::basic_string_view<CharT, Traits>>(rhs);
}

template <typename CharT, std::size_t N, std::size_t M, typename Traits>
constexpr FixedString<CharT, N + M, Traits>
operator+(const FixedString<CharT, N, Traits>& lhs, const FixedString<CharT, M, Traits>& rhs) {
    FixedString<CharT, N + M, Traits> result;
    for (std::size_t i = 0; i < N; ++i)
        result[i] = lhs[i];
    for (std::size_t i = 0; i < M; ++i)
        result[N + i] = rhs[i];
    return result;
}

template <typename CharT, std::size_t N, std::size_t M, typename Traits>
constexpr FixedString<CharT, N - 1 + M, Traits>
operator+(const CharT (&lhs)[N], const FixedString<CharT, M, Traits>& rhs) {
    return FixedString<CharT, N - 1, Traits>(lhs) + rhs;
}

template <typename CharT, std::size_t N, std::size_t M, typename Traits>
constexpr FixedString<CharT, N + M - 1, Traits>
operator+(const FixedString<CharT, N, Traits>& lhs, const CharT (&rhs)[M]) {
    return lhs + FixedString<CharT, M - 1, Traits>(rhs);
}

template <typename CharT, std::size_t N, typename Traits>
constexpr FixedString<CharT, N + 1, Traits>
operator+(CharT lhs, const FixedString<CharT, N, Traits>& rhs) {
    FixedString<CharT, 1, Traits> l;
    l[0] = lhs;
    return l + rhs;
}

template <typename CharT, std::size_t N, typename Traits>
constexpr FixedString<CharT, N + 1, Traits>
operator+(const FixedString<CharT, N, Traits>& lhs, CharT rhs) {
    FixedString<CharT, 1, Traits> r;
    r[0] = rhs;
    return lhs + r;
}

template <typename CharT, std::size_t N, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& out, const FixedString<CharT, N, Traits>& str) {
    out << str.data();
    return out;
}

template <std::size_t N>
using fixed_string = FixedString<char, N>;
template <std::size_t N>
using fixed_wstring = FixedString<wchar_t, N>;
template <std::size_t N>
using fixed_u8string = FixedString<char8_t, N>;
template <std::size_t N>
using fixed_u16string = FixedString<char16_t, N>;
template <std::size_t N>
using fixed_u32string = FixedString<char32_t, N>;

template <typename CharT, std::size_t N>
FixedString(const CharT (&)[N]) -> FixedString<CharT, N - 1>;

} // namespace ModdersDream

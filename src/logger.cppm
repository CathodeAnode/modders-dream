module;
#include <string_view>
export module md.logger;

import std;

export namespace md {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging

namespace LogLevel {

template <std::size_t N>
struct Type {
    char data[N];

    constexpr Type(const char (&str)[N]) {
        std::copy_n(str, N, data);
    }

    constexpr operator std::string_view() const {
        return {data, N - 1};
    }
};

constexpr Type Trace = "TRACE";
constexpr Type Debug = "DEBUG";
constexpr Type Info = "INFO";
constexpr Type Warn = "WARN";
constexpr Type Error = "ERROR";
constexpr Type Fatal = "FATAL";

} // namespace LogLevel

class Logger {
public:
    const std::string category;

    Logger(const std::string& category) : category(category) {}

    template <LogLevel::Type type, typename... Args>
    inline void log(std::format_string<Args...> format, Args&&... args) {
        std::println(
            "[{}] {}: {}",
            std::string_view(type),
            category,
            std::format(format, std::forward<Args>(args)...)
        );
    }
};

} // namespace md

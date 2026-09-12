export module md.logger;

import md.fixed_string;

import std;

export namespace md {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging

namespace LogLevel {

using Type = md::fixed_string;

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

    template <md::fixed_string category, LogLevel::Type type, typename... Args>
    static inline void log(std::format_string<Args...> format, Args&&... args) {
        std::println(
            "[{}] {}: {}",
            std::string_view(type),
            category,
            std::format(format, std::forward<Args>(args)...)
        );
    }
};

} // namespace md

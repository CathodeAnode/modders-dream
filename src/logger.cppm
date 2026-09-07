export module md.logger;

import std;

export namespace md {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging

namespace LogLevel {

using Type = const char*;

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
            type,
            category,
            std::format(format, std::forward<Args>(args)...)
        );
    }
};

} // namespace md

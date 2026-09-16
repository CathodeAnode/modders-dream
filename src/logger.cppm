export module md.logger;

import md.error;

import std;

export namespace md {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging
// TODO: Add way to log into a file

namespace LogLevel {

constexpr std::string_view Trace = "TRACE";
constexpr std::string_view Debug = "DEBUG";
constexpr std::string_view Info = "INFO";
constexpr std::string_view Warn = "WARN";
constexpr std::string_view Error = "ERROR";
constexpr std::string_view Fatal = "FATAL";

} // namespace LogLevel

class Logger {
public:
    const std::string category;

    Logger(const std::string category) : category(std::move(category)) {}

    template <typename... Args>
    inline void log(std::string_view log_level, std::format_string<Args...> format, Args&&... args) {
        std::println(
            "[{}] {}: {}",
            log_level,
            this->category,
            std::format(format, std::forward<Args>(args)...)
        );
    }

    inline static void log(md::Error error) {
        std::println(
            "[{}] {}: {}: {}",
            LogLevel::Error,
            error.system,
            static_cast<std::uint32_t>(error.code),
            error.description
        );
    }
};

} // namespace md

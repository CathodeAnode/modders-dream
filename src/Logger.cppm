export module ModdersDream.Logger;

import ModdersDream.Error;

import std;

export namespace ModdersDream {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging
// TODO: Add way to Log into a file

namespace LogLevel {

constexpr std::string_view Trace = "TRACE";
constexpr std::string_view Debug = "DEBUG";
constexpr std::string_view Info = "INFO";
constexpr std::string_view Warn = "WARN";
constexpr std::string_view Error = "ERROR";
constexpr std::string_view Fatal = "FATAL";
constexpr std::string_view Assert = "ASSERT";

} // namespace LogLevel

class Logger {
public:
    const std::string category;

    Logger(const std::string category) : category(std::move(category)) {}

    template <typename... Args>
    inline void Log(std::string_view logLevel, std::format_string<Args...> format, Args&&... args) {
        std::println(
            "[{}] {}: {}",
            logLevel,
            this->category,
            std::format(format, std::forward<Args>(args)...)
        );
    }

    inline static void Log(ModdersDream::Error error) {
        std::println(
            "[{}] {}: {}: {}",
            LogLevel::Error,
            error.system,
            static_cast<std::uint32_t>(error.code),
            error.description
        );
    }

    template <typename... Args>
    inline static void Assert(std::format_string<Args...> format, Args&&... args) {
        Log(LogLevel::Assert, format, std::forward<Args>(args)...);
        std::abort();
    }
};

} // namespace ModdersDream

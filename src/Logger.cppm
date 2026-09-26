export module ModdersDream.Logger;

import ModdersDream.Error;

import std;

using namespace ModdersDream;

namespace {

template <typename... Args>
struct LocationFormat
{
    std::basic_format_string<char, std::type_identity_t<Args>...> format;
    std::source_location location;

    template <typename T>
        requires std::constructible_from<std::basic_format_string<char, std::type_identity_t<Args>...>, const T&>
    consteval LocationFormat
    (const T& f, std::source_location l = std::source_location::current())
        : format(f), location(l) {}
};

inline const std::chrono::time_point startTime = std::chrono::steady_clock::now();

} // namespace ModdersDream::LoggerDetail

export namespace ModdersDream {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging

enum class LogLevel : std::uint8_t {
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

constexpr std::string_view LogLevelToStringView(LogLevel level) {
    switch (level) {
        case LogLevel::Trace: return "TRACE";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Info: return "INFO";
        case LogLevel::Warn: return "WARN";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Fatal: return "FATAL";
        default: return "";
    }
}

template <LogLevel logLevel, typename... Args>
inline void Log(LocationFormat<Args...> format, Args&&... args) {
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();

    // Would print as "[HH:MM:SS.MS] [LOGLEVEL] [FUNCTION_NAME in FILE_PATH:LINE]: LOG_MESSAGE"
    std::println(
        "[{:02}:{:02}:{:02}.{:03}] [{}] [{} in {}:{}]: {}",
        elapsed / 3'600'000,
        elapsed / 60'000 % 60,
        elapsed / 1000 % 60,
        elapsed % 1000,
        LogLevelToStringView(logLevel),
        format.location.function_name(),
        format.location.file_name(),
        format.location.line(),
        std::format(format.format, std::forward<Args>(args)...)
    );
}

template <LogLevel logLevel, typename... Args>
inline void BasicLog(LocationFormat<Args...> format, Args&&... args) {
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();

    // Would print as "[HH:MM:SS.MS] [LOGLEVEL]: LOG_MESSAGE"
    std::println(
        "[{:02}:{:02}:{:02}.{:03}] [{}]: {}",
        elapsed / 3'600'000,
        elapsed / 60'000 % 60,
        elapsed / 1000 % 60,
        elapsed % 1000,
        std::format(format, std::forward<Args>(args)...),
        LogLevelToStringView(logLevel)
    );
}

template <LogLevel logLevel>
inline void Log(const Error& error) {
    Log<logLevel>("{}: {}", error.code, error.description, error.location);
}

} // namespace ModdersDream

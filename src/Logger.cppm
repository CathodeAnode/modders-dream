export module ModdersDream.Logger;

import ModdersDream.Error;

import std;

using namespace ModdersDream;

namespace {

inline const std::chrono::time_point startTime = std::chrono::steady_clock::now();

} // namespace ModdersDream::LoggerDetail

export namespace ModdersDream {

// TODO: Make argc/argv parser so that logger can have disableable levels of logging

template<class... Args>
struct LocationFormat {
    std::format_string<Args...> format;
    std::source_location location;

    template<class S>
    consteval LocationFormat(
        const S& text,
        std::source_location loc = std::source_location::current())
        : format(text), location(loc) {}
};

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
inline void Log(LocationFormat<std::type_identity_t<Args>...> format, Args&&... args) {
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

template <LogLevel logLevel>
inline void Log(const Error& error) {
    // TODO: Clean this up
    LocationFormat<std::underlying_type_t<ErrorCode>, const std::string&> fmt{"{}: {}"};

    fmt.location = error.location;

    Log<logLevel>(
        fmt,
        std::to_underlying(error.code),
        error.description
    );
}

template <LogLevel logLevel, typename... Args>
inline void BasicLog(std::format_string<Args...> format, Args&&... args) {
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

} // namespace ModdersDream

export module ModdersDream.Error;

import std;

export namespace ModdersDream {

enum class ErrorCode : std::uint32_t {
    None = 0,
    Error,
    InitializationFailed,
    Unsupported
};

struct Error {
    ErrorCode code;
    std::string description;
    std::source_location location;
};

class ErrorHandler {
public:
    bool HasError() const {
        return error_.has_value();
    }

    const Error& GetError() const {
        return *error_;
    }

    ErrorCode GetErrorCode() const {
        return error_.value().code;
    }

    int GetErrorCodeInt() const {
        return static_cast<int>(error_.value().code);
    }

    void ResetError() {
        error_.reset();
    }

protected:
    void SubmitError(
        ErrorCode code,
        const std::string& description,
        std::source_location location = std::source_location::current()
    ) {
        error_ = Error{code, description, location};
    }

private:
    std::optional<Error> error_ = std::nullopt;
};

} // namespace ModdersDream

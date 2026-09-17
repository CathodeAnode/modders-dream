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
    std::string system;
    std::string operation;
    std::string description;
    ErrorCode code = ErrorCode::Error;
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
    void SubmitError(Error error) {
        this->error_ = std::move(error);
    }

private:
    std::optional<Error> error_ = std::nullopt;
};

} // namespace ModdersDream

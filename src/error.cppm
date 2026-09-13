export module md.error;

import std;

export namespace md {

enum class ErrorCode : std::uint32_t {
    None = 0,
    Error,
    InitializationFailed
};

struct Error {
    std::string system;
    std::string operation;
    std::string description;
    ErrorCode code = ErrorCode::Error;
};

class ErrorHandler {
public:
    bool has_error() const {
        return error_.has_value();
    }

    const Error& get_error() const {
        return *error_;
    }

    void reset_error() {
        error_.reset();
    }

protected:
    void submit_error(Error error) {
        this->error_ = std::move(error);
    }

private:
    std::optional<Error> error_ = std::nullopt;
};

} // namespace md

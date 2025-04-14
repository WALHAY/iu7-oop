#include "collection/BaseException.hpp"

BaseException::BaseException(std::string filename, std::string classname, std::string method, int line,
                             std::string error)
{
    this->message =
        "[Exception]\nFilename: " + filename + "\nClassname: " + classname + "\nMethod: " + method + "\nLine: " + std::to_string(line) + "\nDescription: " + error;
}

const char *BaseException::what() const noexcept
{
    return message.c_str();
}

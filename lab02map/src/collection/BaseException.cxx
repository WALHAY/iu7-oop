#include "collection/BaseException.hpp"
#include <cstdio>

BaseException::BaseException(const std::string &filename, const std::string &classname, const std::string &method,
                             int line, const std::string &error) noexcept
{
    snprintf(message, MSG_LENGTH, "File: %s\nClass: %s\nMethod: %s\nLine: %i\nDescription: %s", filename.c_str(),
             classname.c_str(), method.c_str(), line, error.c_str());
	
}

const char *BaseException::what() const noexcept
{
    return message;
}

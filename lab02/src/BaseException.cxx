#include "../inc/BaseException.hpp"
#include <string>

BaseException::BaseException(const std::string message) : message(message) {}

const char *BaseException::what() const noexcept {
	return this->message.c_str();
}

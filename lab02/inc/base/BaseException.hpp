#pragma once

#include <cstdio>
#include <exception>

class BaseException : public std::exception
{
  public:
    explicit BaseException(const char *filename, const char *method, int line, const char *description = "Base Exception!") {
		snprintf(message, MSG_LENGTH, "File: %s\nMethod: %s\nLine: %d\nDescription: %s", filename, method, line, description);
	}

    const char *what() const noexcept override {
		return message;
	}

  protected:
	static constexpr size_t MSG_LENGTH = 512;
	char message[MSG_LENGTH];
};

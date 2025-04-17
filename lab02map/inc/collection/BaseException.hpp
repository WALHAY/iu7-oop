#pragma once

#include <string>

class BaseException : public std::exception
{
  public:
	#define MSG_LENGTH 512

    BaseException(const std::string &filename, const std::string &classname, const std::string &method, int line, const std::string &error) noexcept;

    const char *what() const noexcept override;

	virtual ~BaseException() = default;

  protected:
    char message[MSG_LENGTH];
};

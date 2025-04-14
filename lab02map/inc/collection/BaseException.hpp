#pragma once

#include <string>

class BaseException : public std::exception
{
  public:
    explicit BaseException(std::string filename, std::string classname, std::string method, int line, std::string error);

    const char *what() const noexcept override;

	virtual ~BaseException() = default;

  protected:
    std::string message;
};

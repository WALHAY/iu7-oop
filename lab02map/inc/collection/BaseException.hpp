#pragma once

#include <string>

class BaseException : public std::exception
{
  public:
    explicit BaseException(const std::string message);

    const char *what() const noexcept override;

  protected:
    std::string message;
};

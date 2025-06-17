#pragma once

#include <exception>

class BaseException : public std::exception
{
  public:
    BaseException(const char *filename, const char *method, int line);

    const char *what() const noexcept override;

  private:
    static constexpr int ERR_LEN = 512;
    char ERR_BUF[ERR_LEN];
};


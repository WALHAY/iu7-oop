#pragma once

#include <exception>

class ObjectException : public std::exception
{
  public:
    ObjectException(const char *filename, const char *method, int line);

    const char *what() const noexcept override;

  private:
    static constexpr int ERR_LEN = 512;
    char ERR_BUF[ERR_LEN];
};

class NotImplemented : public ObjectException
{
  public:
    NotImplemented(const char *filename, const char *method, int line) : ObjectException(filename, method, line)
    {
    }
};

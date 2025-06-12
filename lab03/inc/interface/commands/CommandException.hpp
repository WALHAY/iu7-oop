#pragma once

#include <exception>

class CommandException : public std::exception
{
  public:
    CommandException(const char *filename, const char *method, int line);

    const char *what() const noexcept override;

  private:
    static constexpr int ERR_LEN = 512;
    char ERR_BUF[ERR_LEN];
};

class NotImplemented : public CommandException
{
  public:
    NotImplemented(const char *filename, const char *method, int line) : CommandException(filename, method, line)
    {
    }
};

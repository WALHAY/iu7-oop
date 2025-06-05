#pragma once

#include <exception>

class LoaderException : public std::exception
{
  public:
    LoaderException(const char *filename, const char *method, int line);

    const char *what() const noexcept override;

  private:
    static constexpr int ERR_LEN = 512;
    char ERR_BUF[ERR_LEN];
};

class BuilderWrongMethod : public LoaderException
{
  public:
    BuilderWrongMethod(const char *filename, const char *method, int line) : LoaderException(filename, method, line)
    {
    }
};

#pragma once

#include <cstdio>
#include <ctime>
#include <exception>
#include <time.h>

class BaseException : public std::exception
{
  public:
    explicit BaseException(const char *filename, const char *method, int line, time_t time,
                           const char *description = "Base Exception!")
    {
        snprintf(message, MSG_LENGTH, "File: %s\nMethod: %s\nLine: %d\nTime: %s\nDescription: %s", filename, method,
                 line, ctime(&time), description);
    }

    const char *what() const noexcept override
    {
        return message;
    }

  protected:
    static constexpr size_t MSG_LENGTH = 512;
    char message[MSG_LENGTH];
};

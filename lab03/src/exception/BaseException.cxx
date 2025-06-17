#include <cstdio>
#include <exceptions/BaseException.hpp>

BaseException::BaseException(const char *filename, const char *method, int line)
{
    snprintf(ERR_BUF, 512, "Filename: %s\nMethod: %s\nLine: %d\n", filename, method, line);
}

const char *BaseException::what() const noexcept
{
    return ERR_BUF;
}

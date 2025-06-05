#include <cstdio>
#include <loader/LoaderException.hpp>

LoaderException::LoaderException(const char *filename, const char *method, int line)
{
    snprintf(ERR_BUF, 512, "Filename: %s\nMethod: %s\nLine: %d\n", filename, method, line);
}

const char *LoaderException::what() const noexcept
{
    return ERR_BUF;
}

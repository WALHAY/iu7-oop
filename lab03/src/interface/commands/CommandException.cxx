#include <cstdio>
#include <interface/commands/CommandException.hpp>

CommandException::CommandException(const char *filename, const char *method, int line)
{
    snprintf(ERR_BUF, 512, "Filename: %s\nMethod: %s\nLine: %d\n", filename, method, line);
}

const char *CommandException::what() const noexcept
{
    return ERR_BUF;
}

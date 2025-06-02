#include <cstdio>
#include <objects/ObjectException.hpp>

ObjectException::ObjectException(const char *filename, const char *method, int line)
{
    snprintf(ERR_BUF, 512, "Filename: %s\nMethod: %s\nLine: %d\n", filename, method, line);
}

const char *ObjectException::what() const noexcept {
	return ERR_BUF;
}

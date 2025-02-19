#include "../inc/fileio.h"

FILE *open_file(const char *name, const char *mode, int *rc)
{
    FILE *file = fopen(name, mode);
    if (!file)
        *rc = IO_ERR;
    return file;
}

void close_file(FILE *file)
{
    if (file)
        fclose(file);
}

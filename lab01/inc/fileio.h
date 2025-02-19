#pragma once

#include "defines.h"
#include <stdio.h>

FILE *open_file(const char *name, const char *mode, int *rc);

void close_file(FILE *file);

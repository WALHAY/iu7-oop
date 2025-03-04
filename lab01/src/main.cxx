#include "defines.hpp"
#include "application.hpp"
#include "graphics.hpp"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != ARGC)
        return ARGC_ERR;

    graphics_t *graphics = NULL;
    int rc = graphics_init(&graphics);
    if (!rc)
        rc = run_app(*graphics, argv[1]);

    return rc;
}

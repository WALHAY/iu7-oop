#pragma once

#define SDL_SCREEN_WIDTH 1280
#define SDL_SCREEN_HEIGHT 720

#define FIGURE_SCALE 200.0f

#define FPS 144
#define FPS_INTERVAL (1000 / FPS)

#define MOUSE_SENSITIVITY 200.0f

enum error_code
{
    SUCCESS = 0,
    SDL_INIT_FAIL,
    SDL_WINDOW_FAIL,
    MEM_ERR,
    NULLPTR_ERR,
    IO_ERR,
    FMT_ERR
};

#pragma once

#define ARGC 2

#define SDL_SCREEN_WIDTH 1280
#define SDL_SCREEN_HEIGHT 720

#define FPS 144
#define FPS_INTERVAL (1000 / FPS)

#define MOUSE_SENSITIVITY 200.0f

#define SCROLL_MODIFIER 3.0f

#define INIT_SCALE 200.0f

#define SCALE_FACTOR 500.0f

enum error_code
{
    SUCCESS = 0,
	SDL_INIT_ERR,
    MEM_ERR,
    NULLPTR_ERR,
    IO_ERR,
    FMT_ERR,
	ARGC_ERR
};

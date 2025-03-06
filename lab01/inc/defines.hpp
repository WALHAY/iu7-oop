#pragma once

#define ARGC 2

#define SDL_SCREEN_WIDTH 1280
#define SDL_SCREEN_HEIGHT 720

#define FPS 144
#define FPS_INTERVAL (1000 / FPS)

#define INIT_SCALE 200.0f
#define WORLD_SCALE 1000.0f

#define SCALE_MODIFIER 50.0f
#define MOVE_MODIFIER 5.0f
#define ROTATION_MODIFIER 1.0f

#define PI 3.14

enum error_code
{
    SUCCESS = 0,
	SDL_INIT_ERR,
    MEM_ERR,
    NULLPTR_ERR,
    IO_ERR,
    FMT_ERR,
	ARGC_ERR,
	WRONG_EVENT_ERR
};

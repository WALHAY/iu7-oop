#pragma once

#define SDL_SCREEN_WIDTH 1280
#define SDL_SCREEN_HEIGHT 720

#define FPS 60
#define FPS_INTERVAL (1000 / FPS)

enum error_code {
	SUCCESS = 0,
	SDL_INIT_FAIL,
	SDL_WINDOW_FAIL,
	MEM_ERR
};


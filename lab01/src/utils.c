#include "../inc/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

int init_sdl() {
  return SDL_Init(SDL_INIT_EVERYTHING) == 0 ? SUCCESS : SDL_INIT_FAIL;
}

int create_window_and_surface(SDL_Window **window, SDL_Surface **surface) {
  int rc = SUCCESS;
  SDL_Window *new_window = SDL_CreateWindow(
      "OOPLab1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  if (!new_window)
    rc = SDL_WINDOW_FAIL;
  else {
    *window = new_window;

    *surface = SDL_GetWindowSurface(new_window);
  }

  return rc;
}

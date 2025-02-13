#include "../inc/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

int init_sdl() {
  return SDL_Init(SDL_INIT_EVERYTHING) == 0 ? SUCCESS : SDL_INIT_FAIL;
}

int create_window_and_renderer(SDL_Window **window, SDL_Renderer **renderer) {
  int rc = SUCCESS;

  if (SDL_CreateWindowAndRenderer(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN, window, renderer) != 0)
    rc = SDL_WINDOW_FAIL;

  return rc;
}

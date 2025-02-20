#include "../inc/sdltools.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>

int init_sdl()
{
    return SDL_Init(SDL_INIT_EVERYTHING) == 0 ? SUCCESS : SDL_INIT_ERR;
}

int create_window_and_renderer(SDL_Window **window, SDL_Renderer **renderer)
{
    int rc = SUCCESS;

    if (SDL_CreateWindowAndRenderer(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN, window, renderer) != 0)
        rc = SDL_INIT_ERR;

    return rc;
}

void handle_input(figure_state_t *state)
{
    SDL_PumpEvents();
    static int x = 0, y = 0;
    int nx = 0, ny = 0;
    SDL_GetMouseState(&nx, &ny);
    if (nx != x || ny != y)
    {
        state->rotation.x += (x - nx) / MOUSE_SENSITIVITY;
        state->rotation.y += (y - ny) / MOUSE_SENSITIVITY;
        x = nx;
        y = ny;
    }

    const Uint8 *keys = SDL_GetKeyboardState(0);
    if (keys[SDL_SCANCODE_W])
        state->position.y -= 5;
    if (keys[SDL_SCANCODE_S])
        state->position.y += 5;
    if (keys[SDL_SCANCODE_D])
        state->position.x += 5;
    if (keys[SDL_SCANCODE_A])
        state->position.x -= 5;
    if (keys[SDL_SCANCODE_Q])
        state->position.z += 5;
    if (keys[SDL_SCANCODE_E])
        state->position.z -= 5;
}

int draw_loop(SDL_Renderer *renderer, const figure_t *figure, figure_state_t *state)
{
    int rc = SUCCESS;
    bool running = true;

    while (running && !rc)
    {
        if (SDL_QuitRequested())
        {
            running = false;
            break;
        }

        handle_input(state);

        // clear viewport
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        rc = draw_figure(renderer, figure, state);

        SDL_RenderPresent(renderer);

        SDL_Delay(FPS_INTERVAL);
    }
    return rc;
}

void destroy_sdl(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

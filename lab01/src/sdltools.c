#include "../inc/sdltools.h"
#include <SDL2/SDL_events.h>

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

void handle_mouse(int *x, int *y, double *dx, double *dy)
{
    int nx = 0, ny = 0;
    SDL_GetMouseState(&nx, &ny);
    if (nx != *x || ny != *y)
    {
        *dx = (nx - *x) / MOUSE_SENSITIVITY;
        *dy = (ny - *y) / MOUSE_SENSITIVITY;
        *x = nx;
        *y = ny;
    }
}

void handle_keyboard(double *x, double *y, float *scale)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_w:
                    *x -= 1;
                    break;
                case SDLK_s:
                    *x += 1;
                    break;
                case SDLK_d:
                    *y += 5;
                    break;
                case SDLK_a:
                    *y -= 5;
                    break;
            }
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            *scale += event.wheel.y * SCROLL_MODIFIER;
        }
    }
}

int draw_loop(SDL_Renderer *renderer, const figure_t *figure, figure_state_t *state)
{
    int rc = SUCCESS;
    bool running = true;
    int lastX = 0, lastY = 0;

    while (running && !rc)
    {
        if (SDL_QuitRequested())
        {
            running = false;
            break;
        }

        double dx = 0, dy = 0;
        handle_mouse(&lastX, &lastY, &dx, &dy);
        handle_keyboard(&state->position.x, &state->position.y, &state->scale);

        state->rotation.x -= dx;
        state->rotation.y += dy;

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

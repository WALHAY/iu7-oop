#include "../inc/sdltools.h"

int init_sdl()
{
    return SDL_Init(SDL_INIT_EVERYTHING) == 0 ? SUCCESS : SDL_INIT_FAIL;
}

int create_window_and_renderer(SDL_Window **window, SDL_Renderer **renderer)
{
    int rc = SUCCESS;

    if (SDL_CreateWindowAndRenderer(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN, window, renderer) != 0)

        rc = SDL_WINDOW_FAIL;

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

int draw_loop(SDL_Renderer *renderer, const figure_t *figure)
{
    int rc = SUCCESS;
    bool running = true;
    double rotationX = 0, rotationY = 0;
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

        rotationX -= dx;
        rotationY += dy;

        // clear viewport
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        rc = draw_figure(renderer, figure, rotationX, rotationY);

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

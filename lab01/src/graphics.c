#include "../inc/graphics.h"
#include <SDL2/SDL_events.h>

struct graphics_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
};

int graphics_init(graphics_t **graphics)
{
    int rc = SDL_Init(SDL_INIT_EVERYTHING) == 0 ? SUCCESS : SDL_INIT_ERR;

    graphics_t *new_graphics = malloc(sizeof(graphics_t));
    if (new_graphics)
    {
        if (!rc && SDL_CreateWindowAndRenderer(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &new_graphics->window, &new_graphics->renderer) != 0)
            rc = SDL_INIT_ERR;
        else
            *graphics = new_graphics;
    }
    else
        rc = MEM_ERR;
    return rc;
}

int graphics_draw_line(const graphics_t *graphics, float x1, float y1, float x2, float y2)
{
    if (!graphics || !graphics->renderer)
        return NULLPTR_ERR;

    SDL_RenderDrawLineF(graphics->renderer, x1, y1, x2, y2);

    return SUCCESS;
}

int graphics_clear(const graphics_t *graphics)
{
    if (!graphics || !graphics->renderer)
        return NULLPTR_ERR;

    SDL_RenderClear(graphics->renderer);
    return SUCCESS;
}

int graphic_set_color(const graphics_t *graphics, int r, int g, int b, int a)
{
    if (!graphics || !graphics->renderer)
        return NULLPTR_ERR;

    SDL_SetRenderDrawColor(graphics->renderer, r, g, b, a);
    return SUCCESS;
}

int graphics_show(const graphics_t *graphics)
{
    if (!graphics || !graphics->renderer)
        return NULLPTR_ERR;

    SDL_RenderPresent(graphics->renderer);
    return SUCCESS;
}

bool graphics_quit_requested(int *rc, const graphics_t *graphics)
{
    return SDL_QuitRequested();
}

int graphics_delay(const graphics_t *graphics_t, int delay)
{
    SDL_Delay(delay);
    return SUCCESS;
}

int graphics_event_handler(figure_state_t *state, const graphics_t *graphics_t)
{
    if (!state)
        return NULLPTR_ERR;

    SDL_PumpEvents();

    static int x = 0, y = 0;
    static bool mouse_pressed = false;
    int nx = 0, ny = 0;
    SDL_Event event;
    SDL_GetMouseState(&nx, &ny);
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN)
            mouse_pressed = true;
        else if (event.type == SDL_MOUSEBUTTONUP)
            mouse_pressed = false;
    }

    if (mouse_pressed)
    {
        state->rotation.x += (x - nx) / MOUSE_SENSITIVITY;
        state->rotation.y += (y - ny) / MOUSE_SENSITIVITY;
    }
    x = nx;
    y = ny;

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

    if (keys[SDL_SCANCODE_UP])
        state->rotation.y -= 5;
    if (keys[SDL_SCANCODE_DOWN])
        state->rotation.y += 5;
    if (keys[SDL_SCANCODE_LEFT])
        state->rotation.x += 5;
    if (keys[SDL_SCANCODE_RIGHT])
        state->rotation.x -= 5;

    return SUCCESS;
}

bool graphics_valid(const graphics_t *graphics)
{
    return graphics && graphics->renderer && graphics->window;
}

void graphics_destroy(graphics_t *graphics)
{
    if (!graphics)
        return;

    if (graphics->window)
        SDL_DestroyWindow(graphics->window);

    if (graphics->renderer)
        SDL_DestroyRenderer(graphics->renderer);

    free(graphics);

    SDL_Quit();
}

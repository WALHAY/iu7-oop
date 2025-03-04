#include "graphics.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

struct graphics_t
{
    SDL_Window *window;
    SDL_Renderer *renderer;
};

// TODO: rewrite init graphics to init sdl first and allocate memory second
int graphics_init(graphics_t **graphics)
{
    int rc = SDL_Init(SDL_INIT_EVERYTHING) == 0 ? SUCCESS : SDL_INIT_ERR;

    graphics_t *new_graphics = NULL;
	if(!rc)
		new_graphics = (graphics_t*)malloc(sizeof(graphics_t));

    if (!rc && new_graphics)
    {
        if (!rc && SDL_CreateWindowAndRenderer(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &new_graphics->window, &new_graphics->renderer) == -1)
            rc = SDL_INIT_ERR;
        else
            *graphics = new_graphics;
    }
    else
        rc = MEM_ERR;
    return rc;
}

int graphics_draw_line(const graphics_t &graphics, const point2d_t &a, const point2d_t &b)
{
    if (graphics.renderer)
        return NULLPTR_ERR;

    SDL_RenderDrawLineF(graphics.renderer, a.x, a.y, b.x, b.y);

    return SUCCESS;
}

int graphics_clear(const graphics_t &graphics)
{
    if (!graphics.renderer)
        return NULLPTR_ERR;

    SDL_RenderClear(graphics.renderer);
    return SUCCESS;
}

int graphics_set_color(const graphics_t &graphics, int r, int g, int b, int a)
{
    if (!graphics.renderer)
        return NULLPTR_ERR;

    SDL_SetRenderDrawColor(graphics.renderer, r, g, b, a);
    return SUCCESS;
}

int graphics_show(const graphics_t &graphics)
{
    if (!graphics.renderer)
        return NULLPTR_ERR;

    SDL_RenderPresent(graphics.renderer);
    return SUCCESS;
}

int graphics_delay(const graphics_t &graphics, int delay)
{
    SDL_Delay(delay);
    return SUCCESS;
}

void graphics_destroy(graphics_t &graphics)
{
    if (graphics.window)
        SDL_DestroyWindow(graphics.window);

    if (graphics.renderer)
        SDL_DestroyRenderer(graphics.renderer);

    SDL_Quit();
}

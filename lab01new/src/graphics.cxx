#include "graphics.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

struct graphics_t {
	SDL_Window *window;
	SDL_Renderer *renderer;
} graphics;

int init_graphics()
{
	int sdl_error = SDL_CreateWindowAndRenderer(SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &graphics.window, &graphics.renderer);
	return sdl_error == -1 ? ERROR : SUCCESS;
}

int display()
{
	if(!graphics.renderer)
		return ERROR;

	SDL_RenderPresent(graphics.renderer);
	return SUCCESS;
}

int draw_line(const vec2d_t &first, const vec2d_t &second)
{
	if(!graphics.renderer)
		return ERROR;

	SDL_RenderDrawLineF(graphics.renderer, first.x, first.y, second.x, second.y);
	return SUCCESS;
}

int set_color(const color_t &color)
{
	if(!graphics.renderer)
		return ERROR;

	SDL_SetRenderDrawColor(graphics.renderer, get_color_red(color), get_color_green(color), get_color_red(color), get_color_alpha(color));
	return SUCCESS;
}

int destroy_graphics()
{
	if(graphics.window)
		SDL_DestroyWindow(graphics.window);

	if(graphics.renderer)
		SDL_DestroyRenderer(graphics.renderer);

	return SUCCESS;
}

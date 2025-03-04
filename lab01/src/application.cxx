#include "application.hpp"
#include "figure.hpp"
#include "graphics.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>

int run_app(const graphics_t &graphics, const char *figure_path)
{
	static figure_t *figure = NULL;
	if(!figure)
		figure_load(*figure, figure_path);

	bool running = true;
	while(running)
	{
		if(SDL_QuitRequested())
		{
			running = false;
			break;
		}
	
		graphics_set_color(graphics, 255, 255, 255, 255);
		graphics_clear(graphics);

		graphics_show(graphics);
	}
	return 0;
}

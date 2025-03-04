#include "application.hpp"
#include "figure.hpp"
#include "graphics.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>

int run_app(const graphics_t &graphics, const char *figure_path)
{
	figure_t figure;
	int rc = figure_load(figure, figure_path);

	bool running = true;
	while(!rc && running)
	{
		if(SDL_QuitRequested())
		{
			running = false;
			break;
		}
	
		graphics_set_color(graphics, 0, 0, 0, 255);
		graphics_clear(graphics);

		graphics_set_color(graphics, 255, 255, 255, 255);
		edges_draw(graphics,figure.edges);

		figure_move(figure, create_vec3d(0.1, 0, 0));

		graphics_show(graphics);
		graphics_delay(graphics, FPS_INTERVAL);
	}
	return rc;
}

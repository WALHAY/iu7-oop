#include "application.hpp"
#include "figure.hpp"
#include "graphics.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>

int run_app(const graphics_t &graphics, const char *figure_path)
{
	figure_t figure;
	int rc = figure_load(figure, figure_path);

	/*for(size_t i = 0; i < figure->vertices.count; ++i)*/
	/*	printf("%lf %lf %lf", figure->vertices.vertices->x, figure->vertices.vertices->y, figure->vertices.vertices->z);*/

	bool running = true;
	while(!rc && running)
	{
		if(SDL_QuitRequested())
		{
			running = false;
			break;
		}
	
		graphics_set_color(graphics, 255, 255, 255, 255);
		graphics_clear(graphics);

		/*draw_edges(graphics,figure->edges);*/

		graphics_show(graphics);
	}
	return 0;
}

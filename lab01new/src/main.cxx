#include "application.hpp"
#include "graphics.hpp"
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
	int rc = init_graphics();
	set_color(init_rgb(255, 0, 255));
	vec2d_t f = {0, 0};
	vec2d_t s = {100, 100};
	draw_line(f, s);
	display();
	SDL_Delay(5000);
	destroy_graphics();
	return 0;
}

#include "figure.hpp"
#include "point.hpp"

int figure_load(figure_t &figure, const char *figure_path)
{
	int rc = SUCCESS;
	FILE *file = fopen(figure_path, "r");

	if(!file)
		rc = IO_ERR;

	vertices_t vertices;
	edges_t edges;

	if(!rc)
		rc = vertices_load(vertices, file);

	if(!rc)
		rc = edges_load(edges, file, vertices);

	if(!rc)
	{
		figure.center = create_point(0,0,0);
		figure.vertices = vertices;
		figure.edges = edges;
	}

	return rc;
}

void figure_move(figure_t &figure, const point_t &move)
{
	vertices_move(figure.vertices, move);
	point_move(figure.center, move);
}

void figure_rotate(figure_t &figure, const rotation_t &rotation)
{
	vertices_rotate(figure.vertices, figure.center, rotation);
}

void figure_scale(figure_t &figure, double scale)
{
	vertices_scale(figure.vertices, figure.center, scale);
}

int figure_draw(const graphics_t &graphics, const figure_t &figure)
{
	static color_rgb_t black = create_rgba(0,0,0, 255);
	static color_rgb_t white = create_rgba(255,255,255, 255);

	int rc = graphics_set_color(graphics, black);
	if (!rc)
		rc = graphics_clear(graphics);
	
	if(!rc)
		rc = graphics_set_color(graphics, white);

	if(!rc)
		rc = edges_draw(graphics, figure.edges);

	if(!rc)
		rc = graphics_show(graphics);
	return rc;
}

void figure_destroy(figure_t &figure)
{
	vertices_destroy(figure.vertices);
	edges_destroy(figure.edges);
}

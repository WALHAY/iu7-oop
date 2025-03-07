#include "figure.hpp"

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
		figure.center = create_vec3d(0,0,0);
		figure.vertices = vertices;
		figure.edges = edges;
	}

	return rc;
}

void figure_move(figure_t &figure, const point3d_t &offset)
{
	vertices_move(figure.vertices, offset);
	point_move(figure.center, offset);
}

void figure_rotate(figure_t &figure, const rotation3d_t &rotation)
{
	vertices_rotate(figure.vertices, figure.center, rotation);
}

void figure_scale(figure_t &figure, double scale)
{
	vertices_scale(figure.vertices, figure.center, scale);
}

void figure_draw(const graphics_t &graphics, const figure_t &figure)
{
	static color_rgb_t black = create_rgb(0,0,0);
	static color_rgb_t white = create_rgb(255,255,255);

	graphics_set_color(graphics, black);
	graphics_clear(graphics);
	graphics_set_color(graphics, white);
	edges_draw(graphics, figure.edges);
	graphics_show(graphics);
}

void free_figure(figure_t &figure)
{
	vertices_destroy(figure.vertices);
	edges_destroy(figure.edges);
}

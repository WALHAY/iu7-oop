#include "figure.hpp"
#include "point.hpp"
#include "vertices.hpp"

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
		figure.vertices = vertices;
		figure.edges = edges;
	}

	return rc;
}

void figure_move(figure_t &figure, const point3d_t &offset)
{
}

void figure_rotate(figure_t &figure, const point3d_t &center, const rotation3d_t &rotation)
{
}

void figure_scale(figure_t &figure, const point3d_t &center, double scale)
{
}

void free_figure(figure_t &figure)
{
}

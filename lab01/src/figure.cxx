#include "figure.hpp"
#include "edges.hpp"
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
	vertices_move(figure.vertices, offset);
}

void figure_rotate(figure_t &figure, const point3d_t &center, const rotation3d_t &rotation)
{
	vertices_rotate(figure.vertices, center, rotation);
}

void figure_scale(figure_t &figure, const point3d_t &center, double scale)
{
	vertices_scale(figure.vertices, center, scale);
}

void free_figure(figure_t &figure)
{
	vertices_destroy(figure.vertices);
	edges_destroy(figure.edges);
}

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

void free_figure(figure_t &figure)
{
	vertices_destroy(figure.vertices);
	edges_destroy(figure.edges);
}

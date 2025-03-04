#include "edges.hpp"
#include "defines.hpp"
#include "graphics.hpp"
#include "point.hpp"
#include "projection.hpp"
#include "vertices.hpp"
#include <cstdlib>

int read_edge(edge_t *edge, FILE *file, const point3d_t *vertices)
{
	if(!edge)
		return NULLPTR_ERR;

	if(!file)
		return IO_ERR;

	int rc = SUCCESS;
	size_t first = 0;
	size_t second = 0;
	if(fscanf(file, "%zu%zu", &first, &second) != 2)
		rc = FMT_ERR;
	else
	{
		edge->first = vertices + first;
		edge->second = vertices + second;
	}

	return rc;
}

int edges_load(edges_t &edges, FILE *file, const vertices_t &vertices)
{
	if(!file)
		return IO_ERR;

	int rc = SUCCESS;

	size_t count = 0;
	if(fscanf(file, "%zu", &count) != 1)
		rc = IO_ERR;

	edge_t *new_edges = NULL;
	if(!rc)
		new_edges = (edge_t*)malloc(sizeof(edge_t) * count);

	for(size_t i = 0; !rc && i < count; ++i)
		rc = read_edge(new_edges + i, file, vertices.vertices);

	if(rc)
		free(new_edges);
	else {
		edges.count = count;
		edges.edges = new_edges;
	}

	return rc;
}

static int draw_edge(const graphics_t &graphics, const edge_t &edge)
{
	point2d_t first = convert_to_screen(*edge.first);
	point2d_t second = convert_to_screen(*edge.second);
	graphics_draw_line(graphics, first, second);
	return SUCCESS;
}

int edges_draw(const graphics_t &graphics, const edges_t &edges)
{
	for(size_t i = 0; i < edges.count; ++i)
		draw_edge(graphics, edges.edges[i]);
	return SUCCESS;
}

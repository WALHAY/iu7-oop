#include "vertices.hpp"
#include "defines.hpp"
#include "point.hpp"
#include <cstdlib>

static int read_vertex(point3d_t *vertex, FILE *file)
{
	if(!file)
		return IO_ERR;

	int rc = SUCCESS;
	double x, y, z;
	if(fscanf(file, "%lf%lf%lf", &x, &y, &z) != 3)
		rc = FMT_ERR;
	else{
		vertex->x = x;
		vertex->y = y;
		vertex->z = z;
	}

	return rc;
}

int vertices_load(vertices_t &vertices, FILE *file)
{
	if(!file)
		return IO_ERR;

	int rc = SUCCESS;
	size_t count = 0;
	if(fscanf(file, "%zu", &count) != 1)
		rc = FMT_ERR;

	point3d_t *new_vertices = NULL;
	if(!rc)
		new_vertices = (point3d_t*)malloc(sizeof(point3d_t) * count);

	for(size_t i = 0; !rc && i < count; ++i)
		rc = read_vertex(new_vertices + i, file);

	if(rc)
		free(new_vertices);
	else {
		vertices.count = count;
		vertices.vertices = new_vertices;
	}

	return rc;
}

#include "figure.hpp"
#include "point.hpp"

point3d_t read_vertex(FILE *file, int *rc)
{
    point3d_t point;
    if (fscanf(file, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
        *rc = FMT_ERR;
    return point;
}

edge_t read_edge(FILE *file, int *rc)
{
    edge_t edge;
    if (fscanf(file, "%zu %zu", &edge.start, &edge.end) != 2)
        *rc = FMT_ERR;
    return edge;
}

int figure_load(figure_t **figure, const char *figure_path)
{
	return SUCCESS;
}

void figure_move(figure_t &figure, const point3d_t &offset)
{
    for (size_t i = 0; i < figure.vertex_count; ++i)
        point_transpose(figure.vertices[i], offset);
}

void figure_rotate(figure_t &figure, const point3d_t &center, const rotation3d_t &rotation)
{
    for (size_t i = 0; i < figure.vertex_count; ++i)
        point_rotate(figure.vertices[i], center, rotation);
}

void figure_scale(figure_t &figure, const point3d_t &center, double scale)
{
	for(size_t i = 0; i < figure.vertex_count; ++i)
		point_scale(figure.vertices[i], scale);
}

int draw_figure(const graphics_t &graphics, const figure_t &figure)
{
    return SUCCESS;
}

void free_figure(figure_t &figure)
{

}

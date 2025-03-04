#include "../inc/figures.h"

// TODO: те же самые ошибки для данного файла

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

int load_figure(FILE *file, figure_t **figure)
{
    int rc = SUCCESS;
    if (!file)
        rc = IO_ERR;

    size_t edge_count = 0, vertex_count = 0;
    if (!rc && fscanf(file, "%zu %zu", &vertex_count, &edge_count) != 2)
        rc = FMT_ERR;

    figure_t *new_figure = NULL;
    if (!rc)
    {
        new_figure = malloc(sizeof(figure_t) + sizeof(point3d_t) * vertex_count);
        if (!new_figure)
            rc = MEM_ERR;
    }

    edge_t *edges = NULL;
    if (!rc)
    {
        edges = malloc(sizeof(edge_t) * edge_count);
        if (!edges)
            rc = MEM_ERR;
    }

    for (size_t i = 0; !rc && i < vertex_count; ++i)
        new_figure->vertices[i] = read_vertex(file, &rc);

    for (size_t i = 0; !rc && i < edge_count; ++i)
        edges[i] = read_edge(file, &rc);

    if (!rc)
    {
        new_figure->edge_count = edge_count;
        new_figure->vertex_count = vertex_count;
        new_figure->edges = edges;
        *figure = new_figure;
    }
    else
    {
        if (edges)
            free(edges);

        if (new_figure)
            free(new_figure);
    }

    return rc;
}

int figure_move(figure_t *figure, const point3d_t offset)
{
    for (size_t i = 0; i < figure->vertex_count; ++i)
        point_move(figure->vertices + i);
}

int figure_rotate(figure_t *figure, const point3d_t *center, const rotation3d_t *rotation)
{
    for (size_t i = 0; i < figure->vertex_count; ++i)
        point_rotate(figure->vertices + i, center, rotation);
}

int figure_scale(figure_t *figure, const point3d_t *center, double scale)
{
}

int draw_figure(const graphics_t *graphics, const figure_t *figure)
{
    if (graphics == NULL || figure == NULL)
        return NULLPTR_ERR;

    for (size_t i = 0; i < figure->edge_count; ++i)
    {
        point3d_t first = figure->vertices[figure->edges[i].start];
        point3d_t second = figure->vertices[figure->edges[i].end];

        graphics_draw_line(graphics, &first, &second);
    }
    return SUCCESS;
}

void free_figure(figure_t *figure)
{
    if (figure)
    {
        if (figure->edges)
            free(figure->edges);

        free(figure);
    }
}

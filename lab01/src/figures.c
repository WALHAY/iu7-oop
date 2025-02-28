#include "../inc/figures.h"

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

int draw_figure(const graphics_t *graphics, const figure_state_t *state, const figure_t *figure)
{
    if (graphics == NULL || figure == NULL)
        return NULLPTR_ERR;

    for (size_t i = 0; i < figure->edge_count; ++i)
    {
        point3d_t first = figure->vertices[figure->edges[i].start];
        point3d_t second = figure->vertices[figure->edges[i].end];

        first = rotate_y(&first, state->rotation.x);
        second = rotate_y(&second, state->rotation.x);

        first = rotate_x(&first, state->rotation.y);
        second = rotate_x(&second, state->rotation.y);

        first = projection(&first, state->position.z);
        second = projection(&second, state->position.z);

        first = scale_point(&first, state->scale);
        second = scale_point(&second, state->scale);

        first = point_translate(&first, &state->position);
        second = point_translate(&second, &state->position);

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

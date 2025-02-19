#include "../inc/figures.h"
#include <SDL2/SDL_render.h>

#define DISTANCE 1

point3d_t create_point(double x, double y, double z)
{
    point3d_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

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

void scale_figure(figure_t *figure, double scale)
{
    point3d_t *end = figure->vertices + figure->vertex_count;
    for (point3d_t *it = figure->vertices; it < end; ++it)
        *it = scale_point(it, scale);
}

int draw_figure(SDL_Renderer *renderer, const figure_t *figure, double scale, double posX, double posY, double rotX, double rotY)
{
    if (renderer == NULL || figure == NULL)
        return NULLPTR_ERR;

    point3d_t screen_shift = create_point((double)SDL_SCREEN_WIDTH / 2 + posY, (double)SDL_SCREEN_HEIGHT / 2, 0);
    for (size_t i = 0; i < figure->edge_count; ++i)
    {
        point3d_t first = figure->vertices[figure->edges[i].start];
        point3d_t second = figure->vertices[figure->edges[i].end];

        first = rotate_y(&first, rotX);
        second = rotate_y(&second, rotX);

        first = rotate_x(&first, rotY);
        second = rotate_x(&second, rotY);

        first = projection(&first, posX);
        second = projection(&second, posX);

        first = scale_point(&first, scale);
        second = scale_point(&second, scale);

        first = point_translate(&first, &screen_shift);
        second = point_translate(&second, &screen_shift);

        SDL_RenderDrawLineF(renderer, first.x, first.y, second.x, second.y);
    }
    return SUCCESS;
}

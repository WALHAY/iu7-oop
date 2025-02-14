#include "../inc/graphics.h"

point3d_t read_vertex(FILE *file, int *rc) {
  point3d_t point;
  if (fscanf(file, "%lf %lf %lf", &point.x, &point.y, &point.z) != 3)
    *rc = FMT_ERR;
  return point;
}

edge_t read_edge(FILE *file, int *rc) {
  edge_t edge;
  if (fscanf(file, "%zu %zu", &edge.start, &edge.end) != 2)
    *rc = FMT_ERR;
  return edge;
}

int load_figure(FILE *file, figure_t **figure) {
  int rc = SUCCESS;
  if (!file)
    rc = IO_ERR;

  size_t edge_count = 0, vertex_count = 0;
  if (!rc && fscanf(file, "%zu %zu", &vertex_count, &edge_count) != 2)
    rc = FMT_ERR;

  figure_t *new_figure = NULL;
  if (!rc) {
    new_figure = malloc(sizeof(figure_t) + sizeof(point3d_t) * vertex_count);
    if (!new_figure)
      rc = MEM_ERR;
  }

  if (!rc) {
    new_figure->edges = malloc(sizeof(edge_t) * edge_count);
    if (!new_figure->edges)
      rc = MEM_ERR;
  }

  for (size_t i = 0; !rc && i < vertex_count; ++i)
    new_figure->vertices[i] = read_vertex(file, &rc);

  for (size_t i = 0; !rc && i < edge_count; ++i)
    new_figure->edges[i] = read_edge(file, &rc);

  if (rc && new_figure) {
    if (new_figure->edges)
      free(new_figure->edges);
    free(new_figure);
  }

  if (!rc) {
    new_figure->edge_count = edge_count;
    *figure = new_figure;
  }

  return rc;
}

void scale_figure(figure_t *figure, double scale) {
  for (size_t i = 0; i < figure->edge_count; ++i) {
    figure->vertices[i].x *= scale;
    figure->vertices[i].y *= scale;
    figure->vertices[i].z *= scale;
  }
}

int draw_figure(SDL_Renderer *renderer, const figure_t *figure, double rotx,
                double roty) {
  if (renderer == NULL || figure == NULL)
    return NULLPTR_ERR;

  point3d_t screen_shift = {(double)SDL_SCREEN_WIDTH / 2,
                            (double)SDL_SCREEN_HEIGHT / 2, 0};
  for (size_t i = 0; i < figure->edge_count; ++i) {
    point3d_t first = figure->vertices[figure->edges[i].start];
    point3d_t second = figure->vertices[figure->edges[i].end];

    first = rotate_y(&first, rotx);
    second = rotate_y(&second, rotx);

    first = rotate_x(&first, roty);
    second = rotate_x(&second, roty);

    point3d_t start = point_translate(&first, &screen_shift);
    point3d_t end = point_translate(&second, &screen_shift);

    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
  }
  return SUCCESS;
}

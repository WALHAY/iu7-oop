#include "../inc/graphics.h"

int create_cube(figure_t **cube) {
  int rc = SUCCESS;
  figure_t *new_cube =
      (figure_t *)malloc(sizeof(figure_t) + sizeof(point3d_t) * 8);
  if (new_cube) {
    *cube = new_cube;
    new_cube->vertex_count = 8;
    point3d_t vertices[] = {
        {-1, -1, -1}, {-1, -1, 1}, {-1, 1, -1}, {-1, 1, 1},
        {1, -1, -1},  {1, -1, 1},  {1, 1, -1},  {1, 1, 1},
    };

    memcpy(new_cube->vertices, vertices, 8 * sizeof(point3d_t));
  } else
    rc = MEM_ERR;
  return rc;
}

int draw_figure(SDL_Renderer *renderer, const figure_t *figure) {
  for (size_t i = 0; i < figure->vertex_count; ++i) {
    for (size_t j = 0; j < figure->vertex_count; ++j) {
      if (i == j)
        continue;

      point3d_t first = figure->vertices[i];
      point3d_t second = figure->vertices[j];
    }
  }
  return SUCCESS;
}

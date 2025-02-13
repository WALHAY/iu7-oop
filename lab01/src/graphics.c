#include "../inc/graphics.h"
#include <string.h>

#define CUBE_EDGES 12
#define CUBE_VERTICES 8

#define PYRAMID_EDGES 6
#define PYRAMID_VERTICES 4

int create_cube(figure_t **cube) {
  int rc = SUCCESS;
  figure_t *new_cube =
      (figure_t *)malloc(sizeof(figure_t) + sizeof(point3d_t) * CUBE_VERTICES);
  if (new_cube) {
    *cube = new_cube;
    new_cube->edge_count = CUBE_EDGES;

    point3d_t vertices[] = {
        {-1, -1, -1}, {-1, -1, 1}, {-1, 1, -1}, {-1, 1, 1},
        {1, -1, -1},  {1, -1, 1},  {1, 1, -1},  {1, 1, 1},
    };

    memcpy(new_cube->vertices, vertices, CUBE_VERTICES * sizeof(point3d_t));

    new_cube->edges = malloc(sizeof(edge_t) * CUBE_EDGES);
    if (new_cube) {
      edge_t edges[] = {{0, 1}, {0, 4}, {0, 2}, {7, 3}, {7, 6}, {7, 5},
                        {4, 6}, {1, 3}, {1, 5}, {5, 4}, {2, 3}, {2, 6}};

      memcpy(new_cube->edges, edges, sizeof(edge_t) * CUBE_EDGES);
    } else
      rc = MEM_ERR;
  } else
    rc = MEM_ERR;

  if (rc)
    free(new_cube);

  return rc;
}

int create_pyramid(figure_t **cube) {
  int rc = SUCCESS;
  figure_t *new_cube = (figure_t *)malloc(sizeof(figure_t) +
                                          sizeof(point3d_t) * PYRAMID_VERTICES);
  if (new_cube) {
    *cube = new_cube;
    new_cube->edge_count = PYRAMID_EDGES;

    point3d_t vertices[] = {{-1, -1, -1}, {1, -1, -1}, {0, 1, -1}, {0, 0, 10}};

    memcpy(new_cube->vertices, vertices, PYRAMID_VERTICES * sizeof(point3d_t));

    new_cube->edges = malloc(sizeof(edge_t) * PYRAMID_EDGES);
    if (new_cube) {
      edge_t edges[] = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};

      memcpy(new_cube->edges, edges, sizeof(edge_t) * PYRAMID_EDGES);
    } else
      rc = MEM_ERR;
  } else
    rc = MEM_ERR;

  if (rc)
    free(new_cube);

  return rc;
}

void scale_figure(figure_t *figure, double scale) {
  for (size_t i = 0; i < CUBE_VERTICES; ++i) {
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
                            (double)SDL_SCREEN_HEIGHT / 2};
  for (size_t i = 0; i < figure->edge_count; ++i) {
    point3d_t first = figure->vertices[figure->edges[i].start];
    point3d_t second = figure->vertices[figure->edges[i].end];

    first = rotate_y(&first, rotx);
    second = rotate_y(&second, rotx);

    first = rotate_x(&first, roty);
    second = rotate_x(&second, roty);

    point3d_t start = point_translate(&first, &screen_shift);
    point3d_t end = point_translate(&second, &screen_shift);

    SDL_RenderDrawLine(renderer, (int)start.x, (int)start.y, (int)end.x,
                       (int)end.y);
  }
  return SUCCESS;
}

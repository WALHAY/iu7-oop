#include "../inc/figure_state.h"

figure_state_t *init_state(int *rc)
{
    figure_state_t *new_state = malloc(sizeof(figure_state_t));
    if (new_state)
    {
        new_state->position = create_vec3d(SDL_SCREEN_WIDTH / 2.0f, SDL_SCREEN_HEIGHT / 2.0f, 0);
        new_state->rotation = create_vec3d(0, 0, 0);
        new_state->scale = INIT_SCALE;
    }
    else
        *rc = MEM_ERR;
    return new_state;
}

#include "../inc/figure_state.h"

figure_state_t *init_state(int *rc)
{
    figure_state_t *new_state = malloc(sizeof(figure_state_t));
    if (new_state)
    {
        new_state->position = create_point(0, 0, 0);
        new_state->rotation = create_point(0, 0, 0);
        new_state->scale = INIT_SCALE;
    }
    else
        *rc = MEM_ERR;
    return new_state;
}

#include "wolf3d.h"

void     draw_ceiling(int x, int drawStart, t_env *e)
{
    int i;

    if (!e->ceiling_texture)
    {
        i = -1;
        SDL_SetRenderDrawColor(e->renderer, 100,  100, 100, 0);
        while (++i <= drawStart)
            SDL_RenderDrawPoint(e->renderer, x , i);
    }
}

void     draw_floor(int x, int drawEnd, t_env *e)
{
    int i;

    if (!e->floor_texture)
    {
        i = drawEnd - 1;
        SDL_SetRenderDrawColor(e->renderer, 50,  50,  5, 0);
        while (++i < e->pl->screen_height)
            SDL_RenderDrawPoint(e->renderer, x , i);
    }
}
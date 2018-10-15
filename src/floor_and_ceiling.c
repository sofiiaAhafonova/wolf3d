#include "wolf3d.h"
#include <SDL2/SDL_image.h>
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

void load_textures(t_env *e)
{
    e->surface = IMG_Load("pics/eagle.png");

    for(unsigned int x = 0; x < TEX_WIDTH; x++)
    {
        for(unsigned int y = 0; y < TEX_HEIGHT; y++)
        {
            e->floor_texture_data[TEX_WIDTH * y + x] = read_pixel(e->surface, x, y);

        }
    }
}
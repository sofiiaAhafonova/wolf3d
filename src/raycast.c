#include "wolf3d.h"

int		vertical_line(int x, int drawStart, int drawEnd, t_env *e)
{
    SDL_SetRenderDrawColor(e->renderer, e->c.r,  e->c.g,  e->c.b, 0);
    while (drawStart < drawEnd)
    {

        SDL_RenderDrawPoint(e->renderer, x ,drawStart);
        drawStart++;
    }
    return (0);
}

int     raycast(t_env *e)
{
    SDL_Point   step;
    SDL_Point   map;
    int drawStart;
    double perpWallDist;
    int drawEnd;
    int lineHeight;
    int x;

    SDL_SetRenderDrawColor(e->renderer, 0,  0,  0, 0);
    SDL_RenderClear(e->renderer);
    x = -1;
    while (++x < e->player->screen_width)
    {
        //calculate ray position and direction
        e->player->camera = 2 * x / (e->player->screen_width * 1.0) - 1; //x-coordinate in camera space
        e->player->ray_dir.x = e->player->dir.x + e->player->plane.x * e->player->camera;
        e->player->ray_dir.y = e->player->dir.y+ e->player->plane.y * e->player->camera;
        //which box of the map we're in
        map.x = (int) e->player->pos.x;
        map.y = (int) e->player->pos.y;
        e->player->delta_dist.x = fabs(1 / e->player->ray_dir.x);
        e->player->delta_dist.y = fabs(1 / e->player->ray_dir.y);
        e->player->hit = 0; //was there a wall hit?
        e->player->side = 0; //was a NS or a EW wall hit?
        if (e->player->ray_dir.x < 0)
        {
            step.x = -1;
            e->player->side_dist.x = (e->player->pos.x - map.x) * e->player->delta_dist.x;
        }
        else
        {
            step.x = 1;
            e->player->side_dist.x = (map.x + 1.0 - e->player->pos.x) * e->player->delta_dist.x;
        }
        if (e->player->ray_dir.y < 0)
        {
            step.y = -1;
            e->player->side_dist.y = (e->player->pos.y - map.y) * e->player->delta_dist.y;
        }
        else
        {
            step.y = 1;
            e->player->side_dist.y = (map.y + 1.0 - e->player->pos.y) * e->player->delta_dist.y;
        }
        while (e->player->hit == 0)
        {
            if (e->player->side_dist.x < e->player->side_dist.y)
            {
                e->player->side_dist.x += e->player->delta_dist.x;
                map.x += step.x;
                e->player->side = 0;
            }
            else
            {
                e->player->side_dist.y += e->player->delta_dist.y;
                map.y += step.y;
                e->player->side = 1;
            }
            if (e->map->data[map.x][map.y] != '0') e->player->hit = 1;
        }
        if (e->player->side == 0)
            perpWallDist = (map.x - e->player->pos.x + (1 - step.x) / 2) / e->player->ray_dir.x;
        else
            perpWallDist = (map.y - e->player->pos.y + (1 - step.y) / 2) / e->player->ray_dir.y;
        lineHeight = (int)(e->player->screen_height / perpWallDist);
        drawStart = -lineHeight / 2 + e->player->screen_height / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + e->player->screen_height / 2;
        if (drawEnd >= e->player->screen_height)
            drawEnd = e->player->screen_height - 1;
        if (e->map->data[map.x][map.y] == '1')
        {
            e->c.r= 48;
            e->c.g = 190;
            e->c.b = 0;
        }
        else
        {
            e->c.r= 0;
            e->c.g = 190;
            e->c.b = 190;
        }
        if (e->player->side == 1)
        {
            e->c.r /= 2;
            e->c.g /= 2;
            e->c.b /= 2;
        }
        vertical_line(x, drawStart, drawEnd, e);
    }
    SDL_RenderPresent(e->renderer);
    return (0);
}
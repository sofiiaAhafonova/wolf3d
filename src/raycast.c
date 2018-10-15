#include "wolf3d.h"

int		vertical_line(int x, int drawStart, int drawEnd, t_env *e)
{
	int i;

	i = drawStart;
	SDL_SetRenderDrawColor(e->renderer, e->c.r,  e->c.g,  e->c.b, 0);
	while (++i < drawEnd)
		SDL_RenderDrawPoint(e->renderer, x , i);
	return (0);
}
unsigned int	get_color(t_env *e, SDL_Point step)
{
    if (e->pl->side == 1)
    {
        if ((step.x == -1 || step.x == 1 )&& step.y == -1)
            return (1);
        if ((step.x == -1 || step.x == 1) && step.y == 1)
            return (2);
    }
    if (step.x == -1 && (step.y == -1 || step.y == 1))
        return (3);
    return (4);
}

void    choose_color(t_env *e, SDL_Point map,  int color)
{
	if (e->map->data[map.y][map.x] == '1')
	{
		e->c.r= (Uint8)0;
		e->c.g = (Uint8)152;
		e->c.b = (Uint8)0;
        if (color == 2)
        {
            e->c.r= (Uint8)0;
            e->c.g = (Uint8)153;
            e->c.b = (Uint8)60;
        }
	}
	else
	{
		e->c.r= 0;
		e->c.g = 190;
		e->c.b = 190;
        if (color == 2)
        {
            e->c.r= (Uint8)0;
            e->c.g = (Uint8)160;
            e->c.b = (Uint8)160;
        }
	}
    if (color == 3 || color == 4)
    {
        e->c.r = e->c.r >> 2;
        e->c.g = e->c.g >> 2;
        e->c.b =  e->c.b >> 2;
    }
}


void    draw_wall(t_env *e, SDL_Point map, int x, SDL_Point step)
{
	int drawStart;
	double perpWallDist;
	int drawEnd;
	int lineHeight;
    int color;

	if (e->pl->side == 0)
		perpWallDist = (map.x - e->pl->pos.x + (1.0 - step.x) / 2) / e->pl->ray_dir.x;
	else
		perpWallDist = (map.y - e->pl->pos.y + (1.0 - step.y) / 2) / e->pl->ray_dir.y;
    perpWallDist = !perpWallDist ? 1 : perpWallDist;
	lineHeight = (int)(e->pl->screen_height / perpWallDist);
	drawStart = -lineHeight / 2 + e->pl->screen_height / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + e->pl->screen_height / 2;
	if (drawEnd >= e->pl->screen_height)
		drawEnd = e->pl->screen_height - 1;
	color = get_color(e, step);
	draw_ceiling(x, drawStart, e);
	draw_floor(x, drawEnd, e);
	if (!e->wall_texture)
	{
        choose_color(e, map, color);
        vertical_line(x, drawStart, drawEnd, e);
	}
	else
    {
		int texNum = e->map->data[map.y][map.x] - '0' - 1;
		double wallX;
        if (e->pl->side == 0) wallX = e->pl->pos.y + perpWallDist *  e->pl->ray_dir.y;
        else           wallX = e->pl->pos.x + perpWallDist *  e->pl->ray_dir.x;
        wallX -= floor((wallX));
        int texX = (int)(wallX * (double)TEX_WIDTH);
        if(e->pl->side == 0 && e->pl->ray_dir.x > 0) texX = TEX_WIDTH - texX - 1;
        if(e->pl->side == 1 && e->pl->ray_dir.y < 0) texX = TEX_WIDTH - texX - 1;

        for(int y = drawStart; y < drawEnd; y++)
        {
            int d = y * 256 - e->pl->screen_height * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
            int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
            Uint32 col = e->floor_texture_data[TEX_HEIGHT * texY + texX];
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if (color == 2) col = col / 512 ;
            if(color == 3 || color == 4) col = (col >> 1) & 8355711;
            e->c.r = (col >> 16) & 0xff;
            e->c.g = (col >> 8) & 0xff;
            e->c.b = col & 0xff;
            SDL_SetRenderDrawColor(e->renderer, e->c.r,  e->c.g, e->c.b, 0);
            SDL_RenderDrawPoint(e->renderer, x , y);
        }
    }



}


SDL_Point   calc(t_env *e, int x)
{
	SDL_Point   map;

	e->pl->camera = 2 * x / (e->pl->screen_width * 1.0) - 1;
	e->pl->ray_dir.x = e->pl->dir.x + e->pl->plane.x * e->pl->camera;
	e->pl->ray_dir.y = e->pl->dir.y+ e->pl->plane.y * e->pl->camera;
	map.x = (int) e->pl->pos.x;
	map.y = (int) e->pl->pos.y;
	e->pl->delta_dist.x = fabs(1 / e->pl->ray_dir.x);
	e->pl->delta_dist.y = fabs(1 / e->pl->ray_dir.y);
	e->pl->hit = 0;
	e->pl->side = 0;
	return (map);
}

SDL_Point   get_step(t_env *e, SDL_Point map)
{
	SDL_Point step;

	if (e->pl->ray_dir.x < 0)
	{
		step.x = -1;
		e->pl->side_dist.x = (e->pl->pos.x - map.x) * e->pl->delta_dist.x;
	}
	else
	{
		step.x = 1;
		e->pl->side_dist.x = (map.x + 1 - e->pl->pos.x) * e->pl->delta_dist.x;
	}
	if (e->pl->ray_dir.y < 0)
	{
		step.y = -1;
		e->pl->side_dist.y = (e->pl->pos.y - map.y) * e->pl->delta_dist.y;
	}
	else
	{
		step.y = 1;
		e->pl->side_dist.y = (map.y + 1 - e->pl->pos.y) * e->pl->delta_dist.y;
	}
	return (step);
}

SDL_Point   hit_detect(t_env *e, SDL_Point step, SDL_Point map)
{
	while (e->pl->hit == 0)
	{
		if (e->pl->side_dist.x < e->pl->side_dist.y)
		{
			e->pl->side_dist.x += e->pl->delta_dist.x;
			map.x += step.x;
			e->pl->side = 0;
		}
		else
		{
			e->pl->side_dist.y += e->pl->delta_dist.y;
			map.y += step.y;
			e->pl->side = 1;
		}
		if (e->map->data[map.y][map.x] != '0')
			e->pl->hit = 1;
	}
	return (map);
}

int     raycast(t_env *e)
{
	SDL_Point   step;
	SDL_Point   map;
	int x;

	SDL_SetRenderDrawColor(e->renderer, 0,  0,  0, 0);
	SDL_RenderClear(e->renderer);
	x = -1;
	while (++x < e->pl->screen_width)
	{
		map = calc(e, x);
		step = get_step(e, map);
		map = hit_detect(e, step, map);
		draw_wall(e, map, x, step);
	}
	SDL_RenderPresent(e->renderer);
	return (0);
}
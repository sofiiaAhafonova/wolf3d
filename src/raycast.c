#include "wolf3d.h"

SDL_Point		calc(t_env *e, int x)
{
	SDL_Point	map;

	e->pl->camera = 2 * x / (e->pl->screen_width * 1.0) - 1;
	e->pl->ray_dir.x = e->pl->dir.x + e->pl->plane.x * e->pl->camera;
	e->pl->ray_dir.y = e->pl->dir.y + e->pl->plane.y * e->pl->camera;
	map.x = (int)e->pl->pos.x;
	map.y = (int)e->pl->pos.y;
	e->pl->delta_dist.x = fabs(1 / e->pl->ray_dir.x);
	e->pl->delta_dist.y = fabs(1 / e->pl->ray_dir.y);
	e->pl->hit = 0;
	e->pl->side = 0;
	return (map);
}

SDL_Point		get_step(t_env *e, SDL_Point map)
{
	SDL_Point	step;

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

SDL_Point		hit_detect(t_env *e, SDL_Point step, SDL_Point map)
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

int				raycast(t_env *e)
{
	SDL_Point	step;
	SDL_Point	map;
	int			x;

	SDL_SetRenderDrawColor(e->renderer, 0, 0, 0, 0);
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

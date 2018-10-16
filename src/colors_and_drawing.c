#include "wolf3d.h"

void			generate_shades(int y, t_env *e)
{
	int			d;
	Uint32		col;

	d = y * 256 - e->pl->screen_height * 128 + e->lineHeight * 128;
	e->tex.y = ((d * TEX_HEIGHT) / e->lineHeight) / 256;
	col = e->texture[e->text_num][TEX_HEIGHT * e->tex.y + e->tex.x];
	uint_to_rgb(col, e);
	if (e->color == 2)
		e->c.r = e->c.r >> 1;
	if (e->color == 3)
		e->c.g = e->c.b >> 1;
	if (e->color == 4)
		e->c.g = e->c.g >> 1;
}

unsigned int	get_color(t_env *e, SDL_Point step)
{
	if (e->pl->side == 1)
	{
		if ((step.x == -1 || step.x == 1) && step.y == -1)
			return (1);
		if ((step.x == -1 || step.x == 1) && step.y == 1)
			return (2);
	}
	if (step.x == -1 && (step.y == -1 || step.y == 1))
		return (3);
	return (4);
}

void			choose_color(t_env *e, SDL_Point map)
{
	e->c.r = 0;
	if (e->map->data[map.y][map.x] == '1')
	{
		e->c.g = 152;
		e->c.b = 0;
		if (e->color == 2)
			e->c.b = 60;
	}
	else
	{
		e->c.g = 190;
		e->c.b = 190;
		if (e->color == 2)
			e->c.g = 160;
	}
	if (e->color == 3 || e->color == 4)
	{
		e->c.g = e->c.g >> 2;
		e->c.b = e->c.b >> 2;
	}
}

int				vertical_line(int x, t_int_point draw_point, t_env *e, SDL_Point map)
{
	int			y;

	y = draw_point.x;
	e->text_num = e->map->data[map.y][map.x] - '0' - 1;
	if (e->pl->side == 0)
		e->wall.x = e->pl->pos.y + e->perpWallDist * e->pl->ray_dir.y;
	else
		e->wall.x = e->pl->pos.x + e->perpWallDist * e->pl->ray_dir.x;
	e->wall.x -= floor(e->wall.x);
	e->tex.x = (int)(e->wall.x * (double)TEX_WIDTH);
	if (e->pl->side == 0 && e->pl->ray_dir.x > 0)
		e->tex.x = TEX_WIDTH - e->tex.x - 1;
	if (e->pl->side == 1 && e->pl->ray_dir.y < 0)
		e->tex.x = TEX_WIDTH - e->tex.x - 1;
	while (++y < draw_point.y)
	{
		if (e->wall_texture)
			generate_shades(y, e);
		SDL_SetRenderDrawColor(e->renderer, e->c.r, e->c.g, e->c.b, 0);
		SDL_RenderDrawPoint(e->renderer, x, y);
	}
	return (0);
}

void			draw_wall(t_env *e, SDL_Point map, int x, SDL_Point step)
{
	t_int_point		draw_point;

	if (e->pl->side == 0)
		e->perpWallDist = (map.x - e->pl->pos.x +
			(1.0 - step.x) / 2) / e->pl->ray_dir.x;
	else
		e->perpWallDist = (map.y - e->pl->pos.y +
			(1.0 - step.y) / 2) / e->pl->ray_dir.y;
	e->perpWallDist = !e->perpWallDist ? 1 : e->perpWallDist;
	e->lineHeight = (int)(e->pl->screen_height / e->perpWallDist);
	draw_point.x = -e->lineHeight / 2 + e->pl->screen_height / 2;
	if (draw_point.x < 0)
		draw_point.x = 0;
	draw_point.y = e->lineHeight / 2 + e->pl->screen_height / 2;
	if (draw_point.y >= e->pl->screen_height)
		draw_point.y= e->pl->screen_height - 1;
	e->color = get_color(e, step);
	if (!e->wall_texture)
		choose_color(e, map);
	vertical_line(x, draw_point, e, map);
	draw_ceiling(x, draw_point.x, e);
	draw_floor(x, draw_point.y, e, map);
}

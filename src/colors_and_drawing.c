/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_and_drawing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:47:54 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 13:47:59 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			choose_color_end(t_env *e, SDL_Point map)
{
	if (e->map->data[map.y][map.x] == '9')
	{
		e->c.r = 89;
		e->c.g = 136;
		e->c.b = 109;
	}
	if (e->color == 2)
	{
		e->c.r = e->c.r > 0 ? e->c.r >> 2 : 28;
		e->c.b = e->c.b >> 1;
		e->c.g = e->c.g >> 1;
	}
	if (e->color == 3)
		e->c.g = e->c.g >> 2;
	if (e->color == 4)
		e->c.b = e->c.b >> 2;
}

void			choose_color_mid(t_env *e, SDL_Point map)
{
	if (e->map->data[map.y][map.x] == '5')
	{
		e->c.r = 96;
		e->c.g = 187;
		e->c.b = 6;
	}
	else if (e->map->data[map.y][map.x] == '6')
	{
		e->c.r = 241;
		e->c.g = 128;
		e->c.b = 48;
	}
	else if (e->map->data[map.y][map.x] == '7')
	{
		e->c.r = 232;
		e->c.g = 254;
		e->c.b = 109;
	}
	else if (e->map->data[map.y][map.x] == '8')
	{
		e->c.r = 241;
		e->c.g = 128;
		e->c.b = 48;
	}
	choose_color_end(e, map);
}

void			choose_color(t_env *e, SDL_Point map)
{
	if (e->map->data[map.y][map.x] == '1')
	{
		e->c.g = 146;
		e->c.b = 147;
		e->c.r = 0;
	}
	else if (e->map->data[map.y][map.x] == '2')
	{
		e->c.g = 47;
		e->c.b = 31;
		e->c.r = 100;
	}
	else if (e->map->data[map.y][map.x] == '3')
	{
		e->c.g = 203;
		e->c.b = 255;
		e->c.r = 4;
	}
	else if (e->map->data[map.y][map.x] == '4')
	{
		e->c.g = 92;
		e->c.b = 9;
		e->c.r = 241;
	}
	choose_color_mid(e, map);
}

int				vertical_line(int x, t_int_point draw_point, t_env *e,
								SDL_Point map)
{
	int			y;

	y = draw_point.x;
	e->text_num = e->map->data[map.y][map.x] - '0' - 1;
	if (e->pl->side == 0)
		e->wall.x = e->pl->pos.y + e->perp_wall_dist * e->pl->ray_dir.y;
	else
		e->wall.x = e->pl->pos.x + e->perp_wall_dist * e->pl->ray_dir.x;
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
		e->perp_wall_dist = (map.x - e->pl->pos.x +
			(1.0 - step.x) / 2) / e->pl->ray_dir.x;
	else
		e->perp_wall_dist = (map.y - e->pl->pos.y +
			(1.0 - step.y) / 2) / e->pl->ray_dir.y;
	e->perp_wall_dist = !e->perp_wall_dist ? 1 : e->perp_wall_dist;
	e->line_height = (int)(e->pl->screen_height / e->perp_wall_dist);
	draw_point.x = -e->line_height / 2 + e->pl->screen_height / 2;
	if (draw_point.x < 0)
		draw_point.x = 0;
	draw_point.y = e->line_height / 2 + e->pl->screen_height / 2;
	if (draw_point.y >= e->pl->screen_height)
		draw_point.y = e->pl->screen_height - 1;
	e->color = get_color(e, step);
	if (!e->wall_texture)
		choose_color(e, map);
	vertical_line(x, draw_point, e, map);
	draw_ceiling(x, draw_point.x, e);
	draw_floor(x, draw_point.y, e, map);
}

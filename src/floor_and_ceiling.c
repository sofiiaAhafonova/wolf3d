/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:49:04 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 13:49:08 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <SDL_image.h>

void		draw_ceiling(int x, int draw_start, t_env *e)
{
	int		i;

	if (!e->ceiling_texture)
	{
		i = -1;
		SDL_SetRenderDrawColor(e->renderer, 100, 100, 100, 0);
		while (++i <= draw_start)
			SDL_RenderDrawPoint(e->renderer, x, i);
		return ;
	}
}

void		inner_loop(t_env *e, int y, int x, t_floor f)
{
	Uint32	col;

	f.current_dist = e->pl->screen_height / (2.0 * y - e->pl->screen_height);
	f.weight = (f.current_dist - f.dist_player) / (f.dist_wall - f.dist_player);
	f.current_floor.x = f.weight * e->floor_wall.x +
	(1.0 - f.weight) * e->pl->pos.x;
	f.current_floor.y = f.weight * e->floor_wall.y +
	(1.0 - f.weight) * e->pl->pos.y;
	f.floor_tex.x = (int)(f.current_floor.x * TEX_WIDTH) % TEX_WIDTH;
	f.floor_tex.y = (int)(f.current_floor.y * TEX_HEIGHT) % TEX_HEIGHT;
	col = (e->floor_texture_data[TEX_WIDTH * f.floor_tex.y +
	f.floor_tex.x] >> 1) & 8355711;
	uint_to_rgb(col, e);
	SDL_SetRenderDrawColor(e->renderer, e->c.r, e->c.g, e->c.b, 0);
	SDL_RenderDrawPoint(e->renderer, x, y);
	col = e->ceiling_texture_data[TEX_WIDTH * f.floor_tex.y + f.floor_tex.x];
	uint_to_rgb(col, e);
	SDL_SetRenderDrawColor(e->renderer, e->c.r, e->c.g, e->c.b, 0);
	SDL_RenderDrawPoint(e->renderer, x, e->pl->screen_height - y);
}

void		draw_floor(int x, int draw_end, t_env *e, SDL_Point map)
{
	int		y;
	t_floor	f;

	y = draw_end + 1;
	if (!e->floor_texture)
	{
		SDL_SetRenderDrawColor(e->renderer, 50, 50, 5, 0);
		while (y < e->pl->screen_height)
		{
			SDL_RenderDrawPoint(e->renderer, x, y);
			y++;
		}
		return ;
	}
	floor_val(e, map);
	f.dist_wall = e->perp_wall_dist;
	f.dist_player = 0.0;
	if (draw_end < 0)
		draw_end = e->pl->screen_height;
	while (y < e->pl->screen_height)
	{
		inner_loop(e, y, x, f);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:45:54 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 13:45:59 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <SDL_image.h>

void				generate_shades(int y, t_env *e)
{
	int				d;
	Uint32			col;

	d = y * 256 - e->pl->screen_height * 128 + e->line_height * 128;
	e->tex.y = ((d * TEX_HEIGHT) / e->line_height) / 256;
	if (e->color == 2)
		e->text_num += 1;
	else if (e->color == 3)
		e->text_num += 2;
	else if (e->color == 4)
		e->text_num += 3;
	if (e->text_num >= TEX_NUM)
		e->text_num -= 3;
	col = e->texture[e->text_num][TEX_HEIGHT * e->tex.y + e->tex.x];
	uint_to_rgb(col, e);
}

unsigned int		get_color(t_env *e, SDL_Point step)
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

Uint32				*load_textures(char *title)
{
	Uint32			*texture;
	SDL_Surface		*surface;
	int				x;
	int				y;

	surface = IMG_Load(title);
	if (!surface)
		return (NULL);
	if (!(texture = (Uint32*)malloc(sizeof(Uint32) * 64 * 64)))
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	x = -1;
	while (++x < (int)TEX_WIDTH)
	{
		y = -1;
		while (++y < (int)TEX_HEIGHT)
			texture[TEX_WIDTH * y + x] = read_pixel(surface, x, y);
	}
	SDL_FreeSurface(surface);
	return (texture);
}

void				floor_val(t_env *e, SDL_Point map)
{
	if (e->pl->side == 0 && e->pl->ray_dir.x > 0)
	{
		e->floor_wall.x = map.x;
		e->floor_wall.y = map.y + e->wall.x;
	}
	else if (e->pl->side == 0 && e->pl->ray_dir.x < 0)
	{
		e->floor_wall.x = map.x + 1.0;
		e->floor_wall.y = map.y + e->wall.x;
	}
	else if (e->pl->side == 1 && e->pl->ray_dir.y > 0)
	{
		e->floor_wall.x = map.x + e->wall.x;
		e->floor_wall.y = map.y;
	}
	else
	{
		e->floor_wall.x = map.x + e->wall.x;
		e->floor_wall.y = map.y + 1.0;
	}
}

void				load_images(t_env *e)
{
	e->floor_texture_data = load_textures("pics/redbrick.png");
	e->ceiling_texture_data = load_textures("pics/wood.png");
	e->texture[0] = load_textures("pics/WALL75.png");
	e->texture[1] = load_textures("pics/eagle.png");
	e->texture[2] = load_textures("pics/colorstone.png");
	e->texture[3] = load_textures("pics/bluestone.png");
	e->texture[4] = load_textures("pics/greystone.png");
	e->texture[5] = load_textures("pics/WALL65.png");
	e->texture[6] = load_textures("pics/purplestone.png");
	e->texture[7] = load_textures("pics/mossy.png");
	e->texture[8] = load_textures("pics/WALL35.png");
	e->texture[9] = load_textures("pics/WALL19.png");
}

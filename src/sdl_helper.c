/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:50:42 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 13:50:43 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "wolf3d.h"

Uint32		read_pixel(SDL_Surface *surface, const int x, const int y)
{
	int		bpp;
	uint8_t	*p;

	bpp = surface->format->BytesPerPixel;
	p = (uint8_t *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	if (bpp == 2)
		return (*(uint16_t *)p);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	if (bpp == 4)
		return (*(uint32_t *)p);
	return (0);
}

void		uint_to_rgb(Uint32 col, t_env *e)
{
	e->c.r = (col >> 16) & 0xff;
	e->c.g = (col >> 8) & 0xff;
	e->c.b = col & 0xff;
}

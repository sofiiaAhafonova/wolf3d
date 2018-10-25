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

Uint32		read_pixel(SDL_Surface *surf, const int x, const int y)
{
	int		bpp;
	uint8_t	*pxl;

	bpp = surf->format->BytesPerPixel;
	pxl = (uint8_t *)surf->pixels + y * surf->pitch + x * bpp;
	if (bpp == 1)
		return (*pxl);
	if (bpp == 2)
		return (*(uint16_t *)pxl);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (pxl[0] << 16 | pxl[1] << 8 | pxl[2]);
		else
			return (pxl[0] | pxl[1] << 8 | pxl[2] << 16);
	}
	if (bpp == 4)
		return (*(uint32_t *)pxl);
	return (0);
}

void		uint_to_rgb(Uint32 col, t_env *e)
{
	e->c.r = (col >> 16) & 0xff;
	e->c.g = (col >> 8) & 0xff;
	e->c.b = col & 0xff;
}

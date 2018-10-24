#include "wolf3d.h"
#include <SDL_image.h>

Uint32				*load_textures(char *title)
{
	Uint32			*texture;
	SDL_Surface		*surface;
	unsigned int	x;
	unsigned int	y;

	texture = (Uint32*)malloc(sizeof(Uint32) * TEX_HEIGHT * TEX_WIDTH);
	surface = IMG_Load(title);
	if (!surface)
		return (NULL);
	x = 0;
	while (x < TEX_WIDTH)
	{
		y = 0;
		while (y < TEX_HEIGHT)
		{
			texture[TEX_WIDTH * y + x] = read_pixel(surface, x, y);
			y++;
		}
		x++;
	}
	SDL_FreeSurface(surface);
	return (texture);
}

void				uint_to_rgb(Uint32 col, t_env *e)
{
	e->c.r = (col >> 16) & 0xff;
	e->c.g = (col >> 8) & 0xff;
	e->c.b = col & 0xff;
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
   e->texture[0] = load_textures("pics/wood.png");
   e->texture[1] = load_textures("pics/eagle.png");
   e->texture[2] = load_textures("pics/colorstone.png");
   e->texture[3] = load_textures("pics/bluestone.png");
   e->texture[4] = load_textures("pics/greystone.png");
   e->texture[5] = load_textures("pics/redbrick.png");
   e->texture[6] = load_textures("pics/purplestone.png");
   e->texture[7] = load_textures("pics/mossy.png");
   e->texture[8] = load_textures("pics/wood.png");
   e->texture[9] = load_textures("pics/wood.png");
}

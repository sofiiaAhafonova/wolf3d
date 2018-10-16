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
void	uint_to_rgb(Uint32 col, t_env *e)
{
	e->c.r = (col >> 16) & 0xff;
    e->c.g = (col >> 8) & 0xff;
    e->c.b = col & 0xff;
}

void	generate_shades(int lineHeight, int texX, int y, int color, t_env *e)
{
	int d;
    int texY;
    Uint32 col;

    d = y * 256 - e->pl->screen_height * 128 + lineHeight * 128;
    texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
    col = e->floor_texture_data[TEX_HEIGHT * texY + texX];
    uint_to_rgb(col, e);
    if (color == 2)
        e->c.r = e->c.r >> 1;
    if(color == 3)
		e->c.g = e->c.b >> 1;
	if (color == 4)
		e->c.g = e->c.g >> 1;
}

void    draw_wall(t_env *e, SDL_Point map, int x, SDL_Point step)
{
	int drawStart;
	double perpWallDist;
	int drawEnd;
	int lineHeight;
    int color;
    double wallX;
    int texX;

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
        if (e->pl->side == 0) wallX = e->pl->pos.y + perpWallDist *  e->pl->ray_dir.y;
        else           wallX = e->pl->pos.x + perpWallDist *  e->pl->ray_dir.x;
        wallX -= floor((wallX));
        texX = (int)(wallX * (double)TEX_WIDTH);
        if (e->pl->side == 0 && e->pl->ray_dir.x > 0)
        	texX = TEX_WIDTH - texX - 1;
        if (e->pl->side == 1 && e->pl->ray_dir.y < 0)
        	texX = TEX_WIDTH - texX - 1;
        for (int y = drawStart; y < drawEnd; y++)
        {
            generate_shades(lineHeight, texX, y, color, e);
            SDL_SetRenderDrawColor(e->renderer, e->c.r,  e->c.g, e->c.b, 0);
            SDL_RenderDrawPoint(e->renderer, x , y);
        }
        double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
      //4 different wall directions possible
      if(e->pl->side == 0 && e->pl->ray_dir.x > 0)
      {
        floorXWall = map.x;
        floorYWall = map.y + wallX;
      }
      else if(e->pl->side == 0 && e->pl->ray_dir.x < 0)
      {
        floorXWall = map.x + 1.0;
        floorYWall = map.y + wallX;
      }
      else if(e->pl->side == 1 && e->pl->ray_dir.y > 0)
      {
        floorXWall = map.x + wallX;
        floorYWall = map.y;
      }
      else
      {
        floorXWall = map.x + wallX;
        floorYWall = map.y + 1.0;
      }

      double distWall, distPlayer, currentDist;

      distWall = perpWallDist;
      distPlayer = 0.0;

      if (drawEnd < 0) drawEnd = e->pl->screen_height; //becomes < 0 when the integer overflows

      //draw the floor from drawEnd to the bottom of the screen
      for(int y = drawEnd -2; y < e->pl->screen_height; y++)
      {
        currentDist = e->pl->screen_height / (2.0 * y - e->pl->screen_height); //you could make a small lookup table for this instead

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * e->pl->pos.x;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * e->pl->pos.y;

        int floorTexX, floorTexY;
        floorTexX = (int)(currentFloorX * TEX_WIDTH) % TEX_WIDTH;
        floorTexY = (int)(currentFloorY * TEX_HEIGHT) % TEX_HEIGHT;
        Uint32 col = (e->floor_texture_data[TEX_WIDTH * floorTexY + floorTexX] >> 1) & 8355711;
        uint_to_rgb(col, e);
        SDL_SetRenderDrawColor(e->renderer, e->c.r,  e->c.g, e->c.b, 0);
        SDL_RenderDrawPoint(e->renderer, x , y);
        SDL_RenderDrawPoint(e->renderer, x , e->pl->screen_height - y);
        // buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
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
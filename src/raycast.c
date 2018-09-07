#include "wolf3d.h"

int		vertical_line(int x, int drawStart, int drawEnd, t_env *e)
{
    SDL_SetRenderDrawColor(e->renderer, e->c.r,  e->c.g,  e->c.b, 0);
    while (drawStart < drawEnd)
    {

        SDL_RenderDrawPoint(e->renderer, x ,drawStart);
        drawStart++;
    }
    SDL_RenderPresent(e->renderer);
    return (0);
}

int     raycast(t_env *e)
{
    int w = WIN_WIDTH;
    int h = WIN_HEIGHT;
    for(int x = 0; x < w; x++)
    {
        //calculate ray position and direction
        double cameraX = 2 * x / (w * 1.0) - 1; //x-coordinate in camera space
        double rayDirX = e->player->dir_x + e->player->plane_x * cameraX;
        double rayDirY = e->player->dir_y+ e->player->plane_y * cameraX;
        //which box of the map we're in
        int mapX = (int) e->player->pos_x;
        int mapY = (int) e->player->pos_y;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side = 0; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (e->player->pos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - e->player->pos_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (e->player->pos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - e->player->pos_y) * deltaDistY;
        }
        //perform DDA
        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (e->map->data[mapX][mapY] != '0') hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - e->player->pos_x + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - e->player->pos_y + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(h / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + h / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if(drawEnd >= h)drawEnd = h - 1;

        if (e->map->data[mapX][mapY] == '1')
        {
            e->c.r= 48;
            e->c.g = 190;
            e->c.b = 0;
        }
        else
        {
            e->c.r= 0;
            e->c.g = 190;
            e->c.b = 190;
        }
        if (side == 1)
        {
            e->c.r /= 2;
            e->c.g /= 2;
            e->c.b /= 2;
        }

        //draw the pixels of the stripe as a vertical line
        vertical_line(x, drawStart, drawEnd, e);
    }
    return (0);
}
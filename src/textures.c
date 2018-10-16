#include "wolf3d.h"

void    generate_texture(t_env *e)
{
    unsigned int xorcolor;
    unsigned int ycolor;
    unsigned int xycolor;
    int x;
    int y;

    x = -1;
    y = -1;
    while (++x < TEX_WIDTH)
        while (++y < TEX_HEIGHT)
        {
            xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
            ycolor = y * 256 / TEX_HEIGHT;
            xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
            e->texture[0][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
            e->texture[1][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;
            e->texture[2][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
            e->texture[3][TEX_WIDTH * y + x] = 256 * xorcolor;
            e->texture[4][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);
            e->texture[5][TEX_WIDTH * y + x] = 65536 * ycolor;
            e->texture[6][TEX_WIDTH * y + x] = 256 * xorcolor;
            e->texture[7][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y);
            e->texture[8][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
            e->texture[9][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
        }
}

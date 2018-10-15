#include "wolf3d.h"

Uint32    **generate_texture(void)
{

    Uint32 **texture;

    int i = -1;
    texture = (Uint32**)malloc(8 * sizeof(Uint32*));
    while (++i < 8)
        texture[i] = (Uint32*)malloc(TEX_HEIGHT * TEX_WIDTH * sizeof(Uint32));
    for(unsigned int x = 0; x < TEX_WIDTH; x++)
    {
        for(unsigned int y = 0; y < TEX_HEIGHT; y++)
        {
            unsigned int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
            //int xcolor = x * 256 / TEX_WIDTH;
            unsigned int ycolor = y * 256 / TEX_HEIGHT;
            unsigned int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
            texture[7][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red texture with black cross
            texture[0][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
            texture[1][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
            texture[2][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
            texture[3][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
            texture[4][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
            texture[5][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
            texture[6][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
        }
    }
    return (texture);
}

//int draw_texture(int x, int drawStart, int drawEnd, t_env *e, int line_height)
//{
//    for(int y = drawStart; y<drawEnd; y++)
//    {
//        int d = y * 256 - e->pl->screen_height * 128 + line_height * 128;  //256 and 128 factors to avoid floats
//        // TODO: avoid the division to speed this up
//        int texY = ((d * TEX_HEIGHT) / line_height) / 256;
//        Uint32 color = e->texture[texNum][texHeight * texY + texX];
//        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//        if(side == 1) color = (color >> 1) & 8355711;
//        buffer[y][x] = color;
//    }
//}
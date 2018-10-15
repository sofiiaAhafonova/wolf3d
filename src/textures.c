#include "wolf3d.h"

Uint32    **generate_texture(void)
{

    Uint32 **texture;

    int i = -1;
    texture = (Uint32**)malloc(10 * sizeof(Uint32*));
    while (++i < 10)
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
            texture[6][TEX_WIDTH * y + x] = 256 * xorcolor;
            texture[8][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //flat grey texture
            texture[9][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
        }
    }
    return (texture);
}

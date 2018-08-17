#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <SDL.h>
#include "libft.h"

typedef struct  s_map
{
    unsigned int    height;
    unsigned int    width;
    char            **data;
}               t_map;

typedef struct  s_env
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    t_map           *map;
}               t_env;

void            del_node(void *cont, size_t size);
#endif

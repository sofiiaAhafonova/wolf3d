#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <SDL.h>
#include <math.h>
#include "libft.h"

enum
{
    projection_plane_width = 320,
    projection_plane_height = 200,
    projection_plane_center,
    rat_angle = 60 / projection_plane_width
};
typedef struct  s_map
{
    unsigned int    height;
    unsigned int    width;
    char            **data;
}               t_map;

typedef struct  s_player
{
    double x;
    double y;
    double direction;

}               t_player;

typedef struct  s_env
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    t_map           *map;
}               t_env;

void            del_node(void *cont, size_t size);
t_map           *get_map(char *file_name);
void            remove_map(t_map *map);
void            main_loop(t_env env);
void            remove_env(t_env env);
#endif

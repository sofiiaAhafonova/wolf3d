#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <SDL.h>
#include <math.h>
#include "libft.h"

# define FOV 60;
# define WIN_WIDTH 512;
# define WIN_HEIGHT 384;
# define ray_angle 60 / WIN_WIDTH;
# define projection_plane_dist 277



typedef struct  s_map
{
    unsigned int    height;
    unsigned int    width;
    char            **data;
}               t_map;

typedef struct  s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;

}               t_player;

typedef struct  s_color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
}               t_color;

typedef struct  s_env
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Event       event;
    t_map           *map;
    t_player        *player;
    t_color         c;

}               t_env;

t_env           *init_env(t_map *m);
void            del_node(void *cont, size_t size);
t_map           *get_map(char *file_name);
void            remove_map(t_map *map);
void            main_loop(t_env *env);
void            remove_env(t_env *env);
int     raycast(t_env *e);

#endif

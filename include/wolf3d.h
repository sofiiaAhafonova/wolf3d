#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <SDL.h>
#include <math.h>
#include "libft.h"

# define FOV 60;
# define projection_plane_width 320;
# define projection_plane_height 200;
# define ray_angle 60 / projection_plane_width;
# define projection_plane_dist 0.5 * projection_plane_width / tan (0.5 * FOV);
#define ANGLE60 320 //projection_plane_width;
#define ANGLE30 160 //ANGLE60/2;
#define ANGLE15 80 //ANGLE30/2;
#define ANGLE90 480 //ANGLE30*3;
#define ANGLE180 960 //ANGLE90*2;
#define ANGLE270 1440 // ANGLE90*3;
#define ANGLE360 1920 //ANGLE60*6;
#define ANGLE0 0;
#define ANGLE5 26 //ANGLE30/6;
#define ANGLE10 52 //ANGLE5*2;


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
    float           sin_table[ANGLE360];
    float           cos_table[ANGLE360];
    float           tan_table[ANGLE360];
}               t_env;

void            del_node(void *cont, size_t size);
t_map           *get_map(char *file_name);
void            remove_map(t_map *map);
void            main_loop(t_env env);
void            remove_env(t_env env);
#endif

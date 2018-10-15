#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <SDL_mixer.h>
#include "libft.h"
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
typedef struct  s_map
{
    unsigned int    height;
    unsigned int    width;
    char            **data;
}               t_map;

typedef struct  s_point
{
    double x;
    double y;
}               t_point;
typedef struct  s_player
{
    t_point pos;
    t_point dir;
    t_point plane;
    t_point delta_dist;
    t_point side_dist;
    t_point ray_dir;
    double  camera;
    double  rotation_speed;
    double  move_speed;
    int     screen_width;
    int     screen_height;
    int     hit;
    int     side;
    int     height;
    bool    accel;

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
    t_player        *pl;
    t_color         c;
    Uint32          **texture;
    bool            wall_texture;
    bool            floor_texture;
    bool            ceiling_texture;
    Mix_Music       *backgroundSound;

}               t_env;

t_env           *init_env(t_map *m);
void            del_node(void *cont, size_t size);
t_map           *get_map(char *file_name);
void            remove_map(t_map *map);
void            main_loop(t_env *env);
void            remove_env(t_env *env);
int             raycast(t_env *e);
void            draw_ceiling(int x, int drawStart, t_env *e);
void            draw_floor(int x, int drawEnd, t_env *e);

Uint32          **generate_texture(void);

#endif
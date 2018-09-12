#include "wolf3d.h"

t_env   *init_env(t_map *m)
{
    t_env   *env;

    if (!(env = (t_env*)malloc(sizeof(t_env))))
    {
        remove_map(m);
        return (NULL);
    }
    env->map = m;
    if (!(env->player = (t_player*)malloc(sizeof(t_player))))
    {
        remove_env(env);
        return (NULL);
    };
    env->player->pos.x = 2;
    env->player->pos.y = 2;
    env->player->dir.x = -1;
    env->player->dir.y = 0;
    env->player->plane.x = 0;
    env->player->plane.y = 0.66; /* 2d raycaster version of camera plane*/
    env->player->rotation_speed = 0.05;
    env->player->move_speed = 0.05;
    env->player->accel = false;
    env->player->screen_width = 1024;
    env->player->screen_height = 512;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(env->player->screen_width, env->player->screen_height,
            0, &(env->window), &(env->renderer));
    return (env);
}
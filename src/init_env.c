#include "wolf3d.h"

void    find_pos(t_env *e)
{
    int i;
    int j;

    i = -1;
    while (++i < e->map->height)
    {
        j = -1;
        while (++j < e->map->width)
        {
            if (e->map->data[i][j] == '0')
            {
                e->pl->pos.x = j;
                e->pl->pos.y = i;
                return ;
            }
        }
    }
}

t_env   *init_env(t_map *m)
{
    t_env   *env;

    if (!(env = (t_env*)malloc(sizeof(t_env))))
    {
        remove_map(m);
        return (NULL);
    }
    if (!(env->map = m))
        return (NULL);
    if (!(env->pl = (t_player*)malloc(sizeof(t_player))))
    {
        remove_env(env);
        return (NULL);
    };
    find_pos(env);
    env->pl->dir.x = -1;
    env->pl->dir.y = 0;
    env->pl->plane.x = 0;
    env->pl->plane.y = 0.66;
    env->pl->rotation_speed = 0.05;
    env->pl->move_speed = 0.05;
    env->pl->accel = false;
    env->pl->screen_width = 1024;
    env->pl->screen_height = 512;
    env->has_texture = false;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(env->pl->screen_width, env->pl->screen_height,
            0, &(env->window), &(env->renderer));
    return (env);
}
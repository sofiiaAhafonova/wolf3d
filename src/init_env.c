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
    env->player->pos_x = 2;
    env->player->pos_y = 2;
    env->player->dir_x = -1;
    env->player->dir_y = 0;
    env->player->plane_x = 0;
    env->player->plane_y = 0.66; /* 2d raycaster version of camera plane*/

    return (env);
}
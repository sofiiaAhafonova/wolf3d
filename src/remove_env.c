#include "wolf3d.h"

void	del_node(void *cont, size_t size)
{
    if (size && cont)
        free(cont);
}

void    remove_map(t_map *map)
{
    int i;

    if (!map)
        return ;
    i = -1;
    if (map->data)
    {
        while (++i < map->height)
            free(map->data[i]);
        free(map->data);
    }
    free(map);
}

void    remove_env(t_env *env)
{
    int i;

    i = -1;
    if (env->map)
        remove_map(env->map);
    if (env->renderer)
        SDL_DestroyRenderer(env->renderer);
    if (env->window)
       SDL_DestroyWindow(env->window);
    if (env->pl)
        free(env->pl);
    if (env->texture)
    {
        while (++i < 10)
            free(env->texture[i]);
        free(env->texture);
    }
    if (env->backgroundSound)
        Mix_FreeMusic(env->backgroundSound);

    free(env);
    Mix_CloseAudio();
    SDL_Quit();
}
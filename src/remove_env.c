#include "wolf3d.h"

void	del_node(void *cont, size_t size)
{
	if (size && cont)
		free(cont);
}

void	remove_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	if (map->data)
	{
		while (++i < (int)map->height)
			free(map->data[i]);
		free(map->data);
	}
	free(map);
}

void	remove_env(t_env *env)
{
	int	i;

	i = -1;
	if (env->map)
		remove_map(env->map);
	if (env->renderer)
		SDL_DestroyRenderer(env->renderer);
	if (env->window)
		SDL_DestroyWindow(env->window);
	if (env->pl)
		free(env->pl);
	if (env->backgroundSound)
		Mix_FreeMusic(env->backgroundSound);
	while (++i < TEX_NUM)
		free(env->texture[i]);
	if (env->floor_texture_data)
		free(env->floor_texture_data);
	if (env->ceiling_texture_data)
		free(env->ceiling_texture_data);
	free(env);
	Mix_CloseAudio();
	SDL_Quit();
}
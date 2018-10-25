/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:49:26 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 13:49:28 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		find_pos(t_env *e)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (int)e->map->height)
	{
		j = -1;
		while (++j < (int)e->map->width)
		{
			if (e->map->data[i][j] == '0')
			{
				e->pl->pos.x = j + 0.5;
				e->pl->pos.y = i + 0.5;
				return ;
			}
		}
	}
}

void		init_const_vals(t_env *env)
{
	find_pos(env);
	env->pl->dir.x = -1;
	env->pl->dir.y = 0;
	env->pl->plane.x = 0;
	env->pl->plane.y = 0.66;
	env->pl->rotation_speed = 0.25;
	env->pl->move_speed = 0.2;
	env->pl->accel = false;
	env->pl->screen_width = 1200;
	env->pl->screen_height = 600;
	env->wall_texture = true;
	env->floor_texture = true;
	env->ceiling_texture = true;
	env->pl->height = 1;
	load_images(env);
}

t_env		*init_env(t_map *m)
{
	t_env	*env;

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
	}
	init_const_vals(env);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		return (NULL);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	if (!(env->background_sound = Mix_LoadMUS("music/track.mp3")))
		ft_putendl("failed load music");
	SDL_CreateWindowAndRenderer(env->pl->screen_width, env->pl->screen_height,
			0, &(env->window), &(env->renderer));
	return (env);
}

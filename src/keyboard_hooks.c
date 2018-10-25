/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:45:00 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 13:45:05 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

bool			rotate_right(t_env *env)
{
	double buf;

	if (env->event.key.keysym.sym != SDLK_RIGHT &&
		env->event.key.keysym.sym != SDLK_d)
		return (false);
	buf = env->pl->dir.x;
	env->pl->dir.x = env->pl->dir.x * cos(-env->pl->rotation_speed)
			- env->pl->dir.y * sin(-env->pl->rotation_speed);
	env->pl->dir.y = buf * sin(-env->pl->rotation_speed)
			+ env->pl->dir.y * cos(-env->pl->rotation_speed);
	buf = env->pl->plane.x;
	env->pl->plane.x = env->pl->plane.x * cos(-env->pl->rotation_speed)
			- env->pl->plane.y * sin(-env->pl->rotation_speed);
	env->pl->plane.y = buf * sin(-env->pl->rotation_speed)
			+ env->pl->plane.y * cos(-env->pl->rotation_speed);
	return (true);
}

bool			rotate_left(t_env *env)
{
	double buf;

	if (env->event.key.keysym.sym != SDLK_LEFT &&
		env->event.key.keysym.sym != SDLK_a)
		return (false);
	buf = env->pl->dir.x;
	env->pl->dir.x = env->pl->dir.x * cos(env->pl->rotation_speed)
			- env->pl->dir.y * sin(env->pl->rotation_speed);
	env->pl->dir.y = buf * sin(env->pl->rotation_speed)
			+ env->pl->dir.y * cos(env->pl->rotation_speed);
	buf = env->pl->plane.x;
	env->pl->plane.x = env->pl->plane.x * cos(env->pl->rotation_speed)
			- env->pl->plane.y * sin(env->pl->rotation_speed);
	env->pl->plane.y = buf * sin(env->pl->rotation_speed)
			+ env->pl->plane.y * cos(env->pl->rotation_speed);
	return (true);
}

bool			move_back_forth(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_UP ||
		env->event.key.keysym.sym == SDLK_w)
	{
		if (env->map->data[(int)(env->pl->pos.y)][(int)
			(env->pl->pos.x + env->pl->dir.x * env->pl->move_speed)] == '0')
			env->pl->pos.x += env->pl->dir.x * env->pl->move_speed;
		if (env->map->data[(int)(env->pl->pos.y +
			env->pl->dir.y * env->pl->move_speed)][
			(int)(env->pl->pos.x)] == '0')
			env->pl->pos.y += env->pl->dir.y * env->pl->move_speed;
	}
	else if (env->event.key.keysym.sym == SDLK_DOWN ||
		env->event.key.keysym.sym == SDLK_s)
	{
		if (env->map->data[(int)(env->pl->pos.y)][(int)
			(env->pl->pos.x - env->pl->dir.x * env->pl->move_speed)] == '0')
			env->pl->pos.x -= env->pl->dir.x * env->pl->move_speed;
		if (env->map->data[(int)(env->pl->pos.y - env->pl->dir.y
			* env->pl->move_speed)][(int)(env->pl->pos.x)] == '0')
			env->pl->pos.y -= env->pl->dir.y * env->pl->move_speed;
	}
	else
		return (false);
	return (true);
}

void			key_down_events(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_r)
	{
		if (!env->pl->accel)
		{
			env->pl->move_speed = 0.35;
			env->pl->accel = true;
		}
		else
		{
			env->pl->move_speed = 0.2;
			env->pl->accel = false;
		}
		return ;
	}
	else if (env->event.key.keysym.sym == SDLK_t)
	{
		env->wall_texture = env->wall_texture ? false : true;
		env->floor_texture = env->floor_texture ? false : true;
		env->ceiling_texture = env->ceiling_texture ? false : true;
	}
	else if (!rotate_right(env) && !rotate_left(env) && !move_back_forth(env))
		return ;
	raycast(env);
}

void			main_loop(t_env *env)
{
	bool		close_event;

	close_event = false;
	Mix_PlayMusic(env->background_sound, -1);
	raycast(env);
	while (!close_event)
	{
		while (SDL_PollEvent(&(env->event)))
		{
			if (env->event.type == SDL_QUIT)
				close_event = true;
			else if (env->event.type == SDL_KEYDOWN)
			{
				if (env->event.key.keysym.sym == SDLK_ESCAPE)
					close_event = true;
				else
					key_down_events(env);
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sahafono <sahafono@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:12:46 by sahafono          #+#    #+#             */
/*   Updated: 2018/10/25 14:12:50 by sahafono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_WOLF3D_H
# define WOLF3D_WOLF3D_H
# include <SDL.h>
# include <math.h>
# include <stdbool.h>
# include <SDL_mixer.h>
# include "libft.h"
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TEX_NUM 10

typedef struct		s_map
{
	unsigned int	height;
	unsigned int	width;
	char			**data;
}					t_map;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct
{
	int				x;
	int				y;
}					t_int_point;

typedef struct		s_player
{
	t_point			pos;
	t_point			dir;
	t_point			plane;
	t_point			delta_dist;
	t_point			side_dist;
	t_point			ray_dir;
	double			camera;
	double			rotation_speed;
	double			move_speed;
	int				screen_width;
	int				screen_height;
	int				hit;
	int				side;
	int				height;
	bool			accel;

}					t_player;

typedef struct		s_color
{
	Uint8			r;
	Uint8			g;
	Uint8			b;
}					t_color;

typedef struct		s_env
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	t_map			*map;
	t_player		*pl;
	t_color			c;
	Uint32			*texture[TEX_NUM];
	Uint32			*floor_texture_data;
	Uint32			*ceiling_texture_data;
	bool			wall_texture;
	bool			floor_texture;
	bool			ceiling_texture;
	int				text_num;
	Mix_Music		*background_sound;
	double			perp_wall_dist;
	t_point			floor_wall;
	t_point			wall;
	t_int_point		tex;
	double			line_height;
	int				color;
}					t_env;

typedef struct		s_floor
{
	double			weight;
	double			dist_wall;
	double			dist_player;
	double			current_dist;
	Uint32			col;
	t_point			current_floor;
	t_int_point		floor_tex;
}					t_floor;

t_env				*init_env(t_map *m);
void				del_node(void *cont, size_t size);
t_map				*get_map(char *file_name);
void				remove_map(t_map *map);
void				main_loop(t_env *env);
void				remove_env(t_env *env);
int					raycast(t_env *e);
void				draw_ceiling(int x, int draw_start, t_env *e);
void				draw_floor(int x, int draw_end, t_env *e, SDL_Point map);
Uint32				read_pixel(SDL_Surface *surface, const int x, const int y);
void				load_images(t_env *e);
void				uint_to_rgb(Uint32 col, t_env *e);
void				floor_val(t_env *e, SDL_Point map);
int					check_line(char *line, int width);
t_map				*create_map(t_list *lst, unsigned int w, unsigned int h);
void				draw_wall(t_env *e, SDL_Point map, int x, SDL_Point step);
void				generate_shades(int y, t_env *e);
unsigned int		get_color(t_env *e, SDL_Point step);
#endif

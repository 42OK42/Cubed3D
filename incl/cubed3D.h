/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 15:57:03 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED3D_H
# define CUBED3D_H

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

# define M_PI 3.14159265358979323846

typedef struct s_window
{
	void			*mlx;
	void			*mlx_win;
	int				needs_redraw;
}					t_window;

typedef struct s_settings
{
	int		background_color;
	int		wall_color;
	int		player_color;
	int		ray_color;
	int		tile_size;
	int		show_rays;
	int		move_step;
	int		rotation_step;
	float	direction_line_length;
	float	ray_step_size;
	int		num_rays;
	int		fov;
}					t_settings;

typedef struct s_player
{
	float	**player_position;
	int		player_direction;
}					t_player;

typedef struct s_temp
{
	// draw_level
	int		center_x;
	int		center_y;
	int		end_x;
	int		end_y;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	double	angle_rad;
	// raycaster
	float	current_x;
	float	current_y;
	int		next_x;
	int		next_y;
	float	step_x;
	float	step_y;
	float	ray_angle_rad;
	float	ray_distance;
	int		hit_wall;
}					t_temp;

typedef struct s_rays
{
	float		length;
	int			angle;
	int			hit_x;
	int			hit_y;
}			t_rays;

typedef struct s_data
{
	t_window	*window;
	t_settings	*settings;
	t_player	*player;
	t_temp		*temp;
	t_rays		**rays;
	char		*filename;
	char		**map;
	int			map_height;
	int			map_width;
}			t_data;

// close_game.c
int			close_window(void *param);
void		free_map(t_data *data);

//helper.c
void		print_map(t_data *data);

//initialize_data.c
t_data		*initialize_data(void);
t_settings	*initialize_settings(t_data *data);
t_player	*initialize_player(t_data *data);
t_temp		*initialize_temp();
int			find_map_width(t_data *data);
int			find_map_height_before_map(t_data *data);
t_rays		**initialize_rays(t_data *data);

//initialize_player.c
float		**initialize_player_position(t_data *data);
int			initialize_player_direction(t_data	*data, float	**player_position);

// initialize_game.c
t_window	*initialize_window(t_data *data);
char		**map_read(t_data *data);

// draw_level.c
void		draw_element(t_data *data, t_window *window, char c, int c_color);
void		draw_player(t_data *data, t_window *window);
void		draw_ray(t_data *data, t_window *window, float length, int angle);
void		draw_level(t_data *data, t_window *window);

// helper_drawlevel.c
void		bresenham_algorithm(t_data *data, t_window *window);
void		calculate_end_point(t_data *data, int length);
void		draw_tile(t_window *window, int tile_size, int tile_x, int tile_y, int color);

// main.c
int			main(void);

//update_game.c
int			on_press(int keycode, t_data *data);
int			game_loop(t_data *data);
int			on_press(int keycode, t_data *data);
void		update_player_position(t_data *data, char direction);
void		update_player_direction(t_data *data, char direction);
int			update_frame(t_data *data);
int			is_position_walkable(t_data *data, int x, int y);

// raycaster.c
void		raycaster(t_data *data);
void		init_ray_values(t_data *data, float ray_angle);
void		update_ray_position(t_data *data);
int			check_wall_hit(t_data *data);
void		cast_ray(t_data *data, float ray_angle, int i);

# endif

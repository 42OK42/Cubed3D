/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 19:55:23 by okrahl           ###   ########.fr       */
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

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win_minimap;
	void			*mlx_win;
	int				needs_redraw;
}					t_mlx;

typedef struct s_settings
{
	int		window_width;
	int		window_height;
	int		open_minimap;
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
	float	dist_to_proj_plane;
	float 	max_distance;
}					t_settings;

typedef struct s_player
{
	float	**player_position;
	int		player_direction;
}					t_player;

typedef struct s_temp
{
	// draw_minimap
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
	float		hit_x;
	float		hit_y;
}			t_rays;

typedef struct s_data
{
	t_mlx				*mlx;
	t_settings			*settings;
	t_player			*player;
	t_temp				*temp;
	t_rays				**rays;
	char				*filename;
	char				**map;
	int					map_height;
	int					map_width;
}			t_data;

// 3D_visualizer.c
void		draw_3d_view(t_data *data);
void		draw_wall_slice(t_data *data, int x, int wall_height, int color);
void		fill_wall_between_rays(t_data *data, int x0, int x1, int wall_height, int color);

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
t_mlx		*initialize_mlx(t_data *data);
char		**map_read(t_data *data);

// draw_minimap.c
void		draw_element(t_data *data, t_mlx *mlx, char c, int c_color);
void		draw_player(t_data *data, t_mlx *mlx);
void		draw_rays(t_data *data, t_mlx *mlx);
void		draw_ray(t_data *data, t_mlx *mlx, float length, int angle);
void		draw_minimap(t_data *data, t_mlx *mlx);

// helper_drawlevel.c
void		bresenham_algorithm(t_data *data, t_mlx *mlx);
void		calculate_end_point(t_data *data, int length);
void		draw_tile(t_mlx *mlx, int tile_size, int tile_x, int tile_y, int color);

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

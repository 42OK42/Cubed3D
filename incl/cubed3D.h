/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/15 18:22:28 by okrahl           ###   ########.fr       */
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
// ../libraries/libft/

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
	int		space_color;
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

typedef struct s_temp_assets
{
	int		num_colors;
	int		chars_per_pixel;
	int		width;
	int		height;
}					t_temp_assets;

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
	float	previous_x;
	float	previous_y;
	int		next_x;
	int		next_y;
	float	step_x;
	float	step_y;
	float	ray_angle_rad;
	float	ray_distance;
	int		hit_wall;
	//load_assets
	int		width;
	int		height;
	int		num_colors;
	int		chars_per_pixel;
	char	*header;
	char	*color_line;
	char	*pixel_line;
}					t_temp;

typedef struct s_assets
{
	char	*floor_color;
	char	*ceiling_color;
	char	*wall_south_path;
	char	*wall_north_path;
	char	*wall_east_path;
	char	*wall_west_path;
	int		**wall_south;
	int		**wall_north;
	int		**wall_east;
	int		**wall_west;
}					t_assets;

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
	t_assets			*assets;
	char				*filename;
	char				**map;
	int					map_height;
	int					map_width;
}			t_data;

// 3D_visualizer.c
void			draw_3d_view(t_data *data);
void			draw_wall_slice(t_data *data, int x, int wall_height, int *color_row);
void			fill_wall_between_rays(t_data *data, int x0, int x1, int wall_height, int *color_row);
int				**get_right_image(t_data *data, int i);

// close_game.c
int				close_window(void *param);
void			free_map(t_data *data);

//helper.c
void			print_map(char **map);
void			print_colors(char ***colors, int num_colors);
char			*ft_strncpy(char *dest, const char *src, size_t n);
void			print_colored_map_before_hex(char ***colored_map, t_temp_assets *temp);
void			print_image(int **colored_map);
int				get_image_width(int **right_image);
int				get_image_height(int **right_image);
int				ft_atoi_base(char *str, int base);

//initialize_data.c
t_data		*initialize_data(char *filename, t_data *data);
t_settings	*initialize_settings(t_data *data);
t_player	*initialize_player(t_data *data);
t_temp		*initialize_temp();
int			find_map_width(t_data *data);
int			find_map_height_before_map(t_data *data);
t_rays		**initialize_rays(t_data *data);

//initialize_player.c
float			**initialize_player_position(t_data *data);
int				initialize_player_direction(t_data	*data, float	**player_position);

// initialize_game.c
t_mlx			*initialize_mlx(t_data *data);
char			**map_read(t_data *data);

// draw_minimap.c
void			draw_element(t_data *data, t_mlx *mlx, char c, int c_color);
void			draw_player(t_data *data, t_mlx *mlx);
void			draw_rays(t_data *data, t_mlx *mlx);
void			draw_ray(t_data *data, t_mlx *mlx, float length, int angle);
void			draw_minimap(t_data *data, t_mlx *mlx);

// helper_drawlevel.c
void			bresenham_algorithm(t_data *data, t_mlx *mlx);
void			calculate_end_point(t_data *data, int length);
void			draw_tile(t_mlx *mlx, int tile_size, int tile_x, int tile_y, int color);

// main.c
int				main(int argc, char **argv);

//update_game.c
int				on_press(int keycode, t_data *data);
int				game_loop(t_data *data);
int				on_press(int keycode, t_data *data);
void			update_player_position(t_data *data, char direction);
void			update_player_direction(t_data *data, char direction);
int				update_frame(t_data *data);
int				is_position_walkable(t_data *data, int x, int y);

// assets.c
char			**read_xpm(char *PATH);
char			*find_color(char ***colors, int num_colors, char pixel);
char			***get_colors(char **xpm_lines, int num_colors);
char			**get_pixel_map(char **xpm_lines, t_temp_assets *temp);
char			***create_colored_map(char ***colors, int num_colors, char **pixel_map, t_temp_assets *temp);
int				**load_xpm(char *PATH);
t_temp_assets	*parse_header(char **xpm_lines);
t_assets		*initialize_assets(void);

// raycaster.c
void			raycaster(t_data *data);
void			init_ray_values(t_data *data, float ray_angle);
void			update_ray_position(t_data *data);
int				check_wall_hit(t_data *data);
void			cast_ray(t_data *data, float ray_angle, int i);

//free.c
void			free_three_d_array(char ***colors);
void			free_two_d_array(char **pixel_map);
void			free_image(char ***map, int height, int width);
void			free_data_3d(t_data *data);

//alloc_memory.c
char			**malloc_pixel_map(int height, int width);
char			***malloc_color_map(int height, int width);
char			***malloc_color_entries(int num_colors);

int				args_check(int argc, char **argv);

void		cubfile_check(char *mapfile, t_data *data);

void		perror_exit(char *msg);
void		error_exit(char *msg);
void		print_string_array(char **str_array);

int			starts_and_ends_with_wall(char **strarr);
int			no_grey_before_or_after_white(char **strarr);
int			ft_arrlen(char **strarr);
# endif

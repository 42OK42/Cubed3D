/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 15:54:24 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED3D_H
# define CUBED3D_H

// # include <mlx.h>
# include "../libraries/minilibx_opengl_20191021/mlx.h"
# include "../libraries/minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../libraries/libft/libft.h"

# define M_PI 3.14159265358979323846

typedef struct s_point
{
	long double		x;
	long double		y;
}				t_point;
typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win_minimap;
	void			*mlx_win;
	int				needs_redraw;
	void			*img_ptr;
	char			*data_addr;
	void			*old_img_ptr; 
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct s_settings
{
	int			window_width;
	int			window_height;
	int			open_minimap;
	int			background_color;
	int			wall_color;
	int			space_color;
	int			player_color;
	int			upper_background_color;
	int			lower_background_color;
	int			ray_color;
	int			tile_size;
	int			show_rays;
	int			move_step;
	int			rotation_step;
	long double	direction_line_length;
	long double	ray_step_size;
	int			num_rays;
	int			fov;
	long double	dist_to_proj_plane;
	long double	max_distance;
}					t_settings;

typedef struct s_player
{
	long double	**player_position;
	long double	player_direction;
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
	int			center_x;
	int			center_y;
	int			end_x;
	int			end_y;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			next_x;
	int			next_y;
	int			hit_wall;
	int			width;
	int			height;
	int			num_colors;
	int			chars_per_pixel;
	int			screen_x;
	int			exited;
	int			**previous_image;
	char		*header;
	char		*color_line;
	char		*pixel_line;
	double		angle_rad;
	long double	current_x;
	long double	current_y;
	long double	previous_x;
	long double	previous_y;
	long double	step_x;
	long double	step_y;
	long double	ray_angle_rad;
	long double	ray_distance;
	long double	step;
	long double	image_pos;
	long double	d_start_x;
	long double	d_start_y;
	long double	d_curr_x;
	long double	d_curr_y;
	t_point		*start;
	t_point		*sect_with_x;
	t_point		*sect_with_y;
}					t_temp;

typedef struct s_assets
{
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
	long double		length;
	long double		corrected_length;
	long double		acc_corrected_length;
	long double		angle;
	long double		hit_x;
	long double		hit_y;
	int				hinge;
}			t_rays;

typedef struct s_file_info
{
	char		*path_no;
	char		*path_su;
	char		*path_we;
	char		*path_ea;
	char		*f_rgb;
	char		*c_rgb;
	int			fc;
	int			cc;
}			t_file_info;

typedef struct s_data
{
	t_file_info			*file_info;
	t_mlx				*mlx;
	t_settings			*settings;
	t_player			*player;
	t_temp				*temp;
	t_rays				**rays;
	t_assets			*assets;
	long double			grid_x;
	long double			grid_y;
	char				*filename;
	char				*file_content;
	char				*file_copy;
	char				*map_pointer;
	char				**map;
	char				**line_grid;
	char				**row_grid;
	int					map_height;
	int					map_width;
	int					*color_row;
	int					count0;
	int					count1;
	int					count2;
	int					count3;
	int					count4;
	int					count5;
	int					esc;
}			t_data;

long double		fix_fish_eye2(t_data *data, int ray_id);

// 3D_visualizer.c
void			draw_3d_view(t_data *data);
void			draw_wall_slice(t_data *data, int x, double wall_height, \
															int ray_id);
void			fill_wall_between_rays(t_data *data, int prev_screen_x, \
										double wall_height, int ray_id);
void			update_color_row(t_data *data, int ray_id, int start_y, \
															int end_y);
int				calculate_image_x(t_data *data, int ray_id, \
											int image_width);

// 3D_visualizer2.c
long double		fix_fish_eye(t_data *data, int ray_id);
void			draw_background(t_data *data);
void			draw_background_section(t_data *data, \
			int start_y, int end_y, unsigned int color);

//get_image.c
int				**get_right_image(t_data *data, int i);
int				**get_image_for_vertical_hit(t_data *data, int hit_x_int, \
													long double player_x);
int				**get_image_for_horizontal_hit(t_data *data, int hit_y_int, \
													long double player_y);

// close_game.c
int				close_window(t_data *data);
void			free_map(t_data *data);
void			free_data(t_data *data);
void			free_rays(t_rays **rays, int num_rays);
void			free_assets(t_assets *assets);

//helper.c
void			print_map(char **map);
void			print_colors(char ***colors, int num_colors);
void			print_colored_map_before_hex(char ***colored_map, \
											t_temp_assets *temp);
void			print_image(int **colored_map);
void			reset_color_row(t_data *data);

//helper2.c
int				find_map_width(t_data *data);
int				find_map_height_before_map(t_data *data);
int				get_image_width(int **right_image);
int				get_image_height(int **right_image);
int				ft_atoi_base(char *str, int base);

//helper3.c
void			draw_color_row(int *color_row);

//settings.c
t_settings		*initialize_settings(void);
t_settings		*initialize_settings2(t_settings *settings);

//initialize_data.c
t_data			*initialize_data(char *filename, t_data *data);
t_player		*initialize_player(t_data *data);
t_temp			*initialize_temp(void);
t_temp			*initialize_temp2(t_temp *temp);
t_rays			**initialize_rays(t_data *data);

//initialize_player.c
long double		**initialize_player_position(t_data *data);
void			find_player_start_position(t_data *data, \
							long double **player_position);
int				initialize_player_direction(t_data	*data, \
							long double	**player_position);

// initialize_game.c
t_mlx			*initialize_mlx(t_data *data);
char			**map_read(t_data *data);

// draw_minimap.c
void			draw_element(t_data *data, char c, \
										int c_color);
void			draw_player(t_data *data);
void			draw_rays(t_data *data);
void			draw_ray(t_data *data, \
						long double length, int angle);
void			draw_minimap(t_data *data);

// helper_draw_minimap.c
void			calculate_end_point(t_data *data, int length);
void			bresenham_algorithm(t_data *data);
void			initialize_bresenham(t_data *data);
void			update_bresenham(t_data *data);
void			draw_tile(t_data *data, int tile_x, int tile_y, int color);

//parse_file.c
char			*copy_path(char *start, char *end);
char			*extract_path(char **file_content);
char			*extract_color(char **file_content);
void			extract_element(t_data *data, char **file_content);
char			*read_fileinfo(char *file_content, t_data *data);

//parse_file2.c
t_file_info		*initialize_file_info(void);
int				is_element_color(char *file_content, t_data *data);
int				is_element(char *file_content, t_data *data);
size_t			find_length(char *start, char *end);
char			*copy_without_spaces(char *start, char *end);

//parse_file_helper.c
int				parse_rgb_value(const char *str, int *index);
int				rgb_to_hex(const char *rgb);
int				line_is_map(char *file_content);
int				not_all_elements_provided(t_data *data);
char			*skip_empty_lines(char *file_content);
int				map_started(char *file_content);

//parse_file_helper2.c
char			*revert_on_line(char *file_content);
char			*skip_until_map(char *file_content);
char			*skip_empty_lines(char *file_content);

// main.c
int				main(int argc, char **argv);

//update_game.c
int				on_press(int keycode, t_data *data);
int				game_loop(t_data *data);
int				on_press(int keycode, t_data *data);
int				update_frame(t_data *data);
//update_player.c
void			update_player_position(t_data *data, char direction);
void			calculate_new_position(t_data *data, char direction, \
				long double *new_x, long double *new_y);
void			update_player_direction(t_data *data, char direction);
int				is_position_walkable(t_data *data, long double x, \
													long double y);
int				check_buffer_zones(t_data *data, long double x, long double y);

// prepare_assets.c
void			initialize_assets(t_data *data);
int				**load_xpm(char *PATH);
char			**read_xpm(char *PATH);

// prepare_assets2.c
int				hex_to_decimal(const char *hex_str);
int				**convert_to_hex(char ***image_before, t_temp_assets *temp);
char			*find_color(char ***colors, int num_colors, char pixel);
char			***get_colors(char **xpm_lines, int num_colors);
t_temp_assets	*parse_header(char **xpm_lines);

// prepare_assets3.c
char			**get_pixel_map(char **xpm_lines, t_temp_assets *temp);
char			***create_colored_map(char ***colors, \
				int num_colors, char **pixel_map, t_temp_assets *temp);

// raycaster.c
void			raycaster(t_data *data);
void			init_ray_values(t_data *data, long double ray_angle);
int				check_wall_hit(t_data *data);
void			cast_ray(t_data *data, long double ray_angle, int i);

//free_assets.c
void			free_three_d_array(char ***colors);
void			free_two_d_array(char **pixel_map);
void			free_image(char ***map, int height, int width);
void			free_data_3d(t_data *data);
void			free_two_d_int_array(int **int_array);

//free_data.c
void			free_mlx(t_data *data);

//alloc_memory.c
char			**malloc_pixel_map(int height, int width);
char			***malloc_color_map(int height, int width);
char			***malloc_color_entries(int num_colors);
int				*initialize_color_row(t_data *data);

//cubfile_check.c
int				args_check(int argc, char **argv);
void			cubfile_check(char *mapfile, t_data *data);

//utils.c
void			perror_exit(char *msg);
void			error_exit(char *msg);
void			print_string_array(char **str_array);
int				no_grey_before_or_after_white(char **strarr);
int				ft_arrlen(char **strarr);

//utils2.c
int				starts_and_ends_with_wall(char **strarr);
int				closest_multiple_of_tile(int num, int tile_size);
int				same_but_reverse(char **strarr, int len);
long double		distance(t_point *start, t_point *end);
long double		absolute_difference(long double num1, long double num2);

//utils3.c
int				valid_map_chars(char *str);
int				only_valid_map_chars(char *str);
int				find_max_width(char **line_grid);
int				pad(char **line_grid, int max_width);
char			**malloc_row_grid(char **line_grid);

//utils4.c
t_point			*backtrack_to_y(t_data *data);
t_point			*backtrack_to_x(t_data *data);
int				calculate_image_x(t_data *data, int ray_id, int image_width);
int				xor(int a, int b);
int				neither_in_range(t_data *data);

//utils5.c
long double		adjust_towards_closest_multiple_by(long double current_x, \
							long double tile_size, long double inch);
void			init_ray_values(t_data *data, long double ray_angle);
void			update_ray_position(t_data *data, int j);
void			free_ray_loop(t_data *data);

//utils6.c
int				no_grey_before_or_after_player(char **strarr);
int				check__invalid_chars(char **strarr);
int				check_chars(char **strarr);

//corner_utils.c
int				southeast(t_data *data);
int				southwest(t_data *data);
int				northeast(t_data *data);
int				northwest(t_data *data);
//corner_utils2.c
int				southeast_corner(t_data *data, int cell_x, int cell_y);
int				southwest_corner(t_data *data, int cell_x, int cell_y);
int				northeast_corner(t_data *data, int cell_x, int cell_y);
int				northwest_corner(t_data *data, int cell_x, int cell_y);

//wall_checks.c
int				north_wall_crossing(t_data *data, int hit_x_int, int hit_y_int);
int				south_wall_crossing(t_data *data, int hit_x_int, int hit_y_int);
int				west_wall_crossing(t_data *data, int hit_x_int, int hit_y_int);
int				east_wall_crossing(t_data *data, int hit_x_int, int hit_y_int);

//wall_checks_small.c
int				north_wall(t_data *data, long double hit_x_f, int hit_y_int);
int				south_wall(t_data *data, long double hit_x_f, int hit_y_int);
int				east_wall(t_data *data, long double hit_y_f, int hit_x_int);
int				west_wall(t_data *data, long double hit_y_f, int hit_x_int);

//backtrack.cd
t_point			*get_true_intersection(t_point *start, t_data *data, \
														t_temp *temp);
#endif
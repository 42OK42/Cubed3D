/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/23 12:58:06 by okrahl           ###   ########.fr       */
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
# include "libft.h"


typedef struct s_window
{
	void			*mlx;
	void			*mlx_win;
}					t_window;

typedef struct s_settings
{
	int	background_color;
	int	wall_color;
	int	player_color;
	int	tile_size;
}					t_settings;

typedef struct s_player
{
	int	**player_position;
	int	player_direction;
}					t_player;

typedef struct s_data
{
	t_window	*window;
	t_settings	*settings;
	t_player	*player;
	char		*filename;
	char		**map;
	int			map_height;
	int			map_width;
}			t_data;

// close_game.c
int		close_window(void *param);
void	free_map(t_data *data);

//helper.c
void	print_map(t_data *data);

//initialize_data.c
t_data	*initialize_data(void);
t_settings	*initialize_settings(t_data *data);
t_player	*initialize_player(t_data *data);
int	find_map_width(t_data *data);
int	find_map_height_before_map(t_data *data);

//initialize_player.c
int	**initialize_player_position(t_data *data);
int	initialize_player_direction(t_data	*data, int	**player_position);

// initialize_game.c
t_window	*initialize_window(t_data *data);
char	**map_read(t_data *data);
void	draw_element(t_data *data, t_window *window, char c, int c_color);
void	draw_tile(t_window *window, int tile_size, int tile_x, int tile_y, int color);
void	draw_player(t_data *data, t_window *window);

// main.c
int	main(void);

//update_game.c
int	on_press(int keycode, t_data *data);
int	game_loop(t_data *data);
int	on_press(int keycode, t_data *data);




# endif

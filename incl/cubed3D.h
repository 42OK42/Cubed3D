/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 20:25:05 by okrahl           ###   ########.fr       */
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
	int	tile_size;
}					t_settings;

typedef struct s_data
{
	t_window	*window;
	t_settings	*settings;
	char	*filename;
	char	**map;
	int		map_height;
	int		map_width;
}			t_data;

// close_game.c
int		close_window(void *param);
void	free_map(t_data *data);

//helper.c
void	print_map(t_data *data);

//initialize_data.c
t_data	*initialize_data(void);
t_settings	*initialize_settings(t_data *data);
int	find_map_width(t_data *data);
int	find_map_height_before_map(t_data *data);

// initialize_game.c
t_window	*initialize_window(t_data *data);
char	**map_read(t_data *data);
void	draw_background(t_data *data, t_window *window);
void	draw_walls(t_data *data, t_window *window);

// main.c
int	main(void);

//update_game.c
int	on_press(int keycode, t_data *data);
int	game_loop(t_data *data);
int	on_press(int keycode, t_data *data);




# endif

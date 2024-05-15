/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 18:44:54 by okrahl           ###   ########.fr       */
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

typedef struct s_data
{
	t_window	*window;
	char	*filename;
	char	**map;
	int		map_height;
	int		map_width;
}			t_data;

// initialize_game.c
t_window	*initialize_window(t_data *data);
char	**map_read(t_data *data);

//helpers.c
t_data	*initialize_data(void);
void	print_map(t_data *data);

// close_game.c
int		close_window(void *param);
void	free_map(t_data *data);

# endif

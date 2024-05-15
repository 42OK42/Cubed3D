/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed3D.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:19:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 16:52:48 by okrahl           ###   ########.fr       */
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

typedef struct s_data
{
	char	*filename;
	char	**map;
	int		map_height;
	int		map_width;
}			t_data;

// initialize_game.c
char	**map_read(t_data *data);
void	*open_window(void	*mlx, t_data *data);
t_data	*initialize_data(void);

//helpers.c
void	print_map(t_data *data);

# endif

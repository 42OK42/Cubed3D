/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:52:48 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 17:46:54 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

float	**initialize_player_position(t_data *data)
{
	float	**player_position;

	player_position = malloc(sizeof(float *) * 2);
	if (!player_position)
		return (0);
	player_position[0] = malloc(sizeof(float) * 2);
	if (!player_position[0])
		return (0);
	find_player_start_position(data, player_position);
	return (player_position);
}

void	find_player_start_position(t_data *data, float **player_position)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data->map[y][x] && data->map[y][x] != 'N' && \
		data->map[y][x] != 'E' && data->map[y][x] != 'W' \
		&& data->map[y][x] != 'S')
	{
		while (data->map[y][x] && data->map[y][x] != 'N' \
			&& data->map[y][x] != 'E' && data->map[y][x] != 'W' \
			&& data->map[y][x] != 'S')
			x++;
		if (data->map[y][x] == 'N' || data->map[y][x] == 'E' \
			|| data->map[y][x] == 'W' || data->map[y][x] == 'S')
			break ;
		y++;
		x = 0;
	}
	player_position[0][0] = (float)(x * \
		data->settings->tile_size + data->settings->tile_size / 2);
	player_position[0][1] = (float)(y * \
		data->settings->tile_size + data->settings->tile_size / 2);
}

int	initialize_player_direction(t_data *data, float **player_position)
{
	int		tile_x;
	int		tile_y;
	char	direction_char;

	tile_x = (int)(player_position[0][0]) / data->settings->tile_size;
	tile_y = (int)(player_position[0][1]) / data->settings->tile_size;
	direction_char = data->map[tile_y][tile_x];
	if (direction_char == 'N')
		return (0);
	else if (direction_char == 'E')
		return (90);
	else if (direction_char == 'S')
		return (180);
	else if (direction_char == 'W')
		return (270);
	else
		return (-1);
}

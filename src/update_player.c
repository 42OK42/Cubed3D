/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:54:21 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 18:09:32 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	update_player_position(t_data *data, char direction)
{
	float	new_x;
	float	new_y;

	calculate_new_position(data, direction, &new_x, &new_y);
	if (is_position_walkable(data, new_x, new_y))
	{
		data->player->player_position[0][0] = new_x;
		data->player->player_position[0][1] = new_y;
	}
}

void	calculate_new_position(t_data *data, char direction, \
	float *new_x, float *new_y)
{
	int		move_step;
	double	angle_rad;

	move_step = data->settings->move_step;
	angle_rad = (data->player->player_direction - 90) * M_PI / 180.0;
	if (direction == 'u')
	{
		*new_x = data->player->player_position[0][0] + \
			(move_step * cos(angle_rad));
		*new_y = data->player->player_position[0][1] + \
			(move_step * sin(angle_rad));
	}
	else if (direction == 'd')
	{
		*new_x = data->player->player_position[0][0] - \
			(move_step * cos(angle_rad));
		*new_y = data->player->player_position[0][1] - \
			(move_step * sin(angle_rad));
	}
	else
	{
		*new_x = data->player->player_position[0][0];
		*new_y = data->player->player_position[0][1];
	}
}

void	update_player_direction(t_data *data, char direction)
{
	int	rotate_step;

	rotate_step = data->settings->rotation_step;
	if (direction == 'l')
	{
		data->player->player_direction -= rotate_step;
		if (data->player->player_direction < 0)
			data->player->player_direction += 360;
	}
	else if (direction == 'r')
	{
		data->player->player_direction += rotate_step;
		if (data->player->player_direction >= 360)
			data->player->player_direction -= 360;
	}
}

int	is_position_walkable(t_data *data, float x, float y)
{
	int		tile_size;
	int		map_x;
	int		map_y;

	tile_size = data->settings->tile_size;
	map_x = x / tile_size;
	map_y = y / tile_size;
	if (data->map[map_y][map_x] == '1')
		return (0);
	return (check_buffer_zones(data, x, y));
}

int	check_buffer_zones(t_data *data, float x, float y)
{
	int		tile_size;
	float	buffer;
	int		map_x;
	int		map_y;

	tile_size = data->settings->tile_size;
	map_x = x / tile_size;
	map_y = y / tile_size;
	buffer = tile_size * 0.05;
	if (x - (map_x * tile_size) < buffer && map_x > 0 && \
		data->map[map_y][map_x - 1] == '1')
		return (0);
	if ((map_x + 1) * tile_size - x < buffer && map_x \
		< data->map_width - 1 && data->map[map_y][map_x + 1] == '1')
		return (0);
	if (y - (map_y * tile_size) < buffer && map_y > 0 \
		&& data->map[map_y - 1][map_x] == '1')
		return (0);
	if ((map_y + 1) * tile_size - y < buffer && map_y < \
		data->map_height - 1 && data->map[map_y + 1][map_x] == '1')
		return (0);
	return (1);
}

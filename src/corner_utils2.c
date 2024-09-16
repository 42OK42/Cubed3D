/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:36:14 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 19:36:17 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	southeast_corner(t_data *data, int cell_x, int cell_y)
{
	if ((int)data->temp->current_x % data->settings->tile_size == 0 \
	&& (int)data->temp->current_y % data->settings->tile_size == 0)
	{
		if (data->map[cell_y][cell_x -1] == '1' \
			&& data->map[cell_y -1][cell_x] == '1')
			return (1);
	}
	return (0);
}

int	southwest_corner(t_data *data, int cell_x, int cell_y)
{
	if (((int)data->temp->current_x + 1) % data->settings->tile_size == 0 \
	&& (int)data->temp->current_y % data->settings->tile_size == 0)
	{
		if (data->map[cell_y -1][cell_x] == '1' \
			&& data->map[cell_y][cell_x +1] == '1')
			return (1);
	}
	return (0);
}

int	northwest_corner(t_data *data, int cell_x, int cell_y)
{
	if (((int)data->temp->current_x + 1) % data->settings->tile_size == 0 \
		&& ((int)data->temp->current_y + 1) % data->settings->tile_size == 0)
	{
		if (data->map[cell_y][cell_x +1] == '1' \
		&& data->map[cell_y +1][cell_x] == '1')
			return (1);
	}
	return (0);
}

int	northeast_corner(t_data *data, int cell_x, int cell_y)
{
	if ((int)data->temp->current_x % data->settings->tile_size == 0 \
	&& ((int)data->temp->current_y + 1) % data->settings->tile_size == 0)
	{
		if (data->map[cell_y][cell_x -1] == '1' \
			&& data->map[cell_y +1][cell_x] == '1')
			return (1);
	}
	return (0);
}

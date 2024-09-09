/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:36:07 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 19:36:10 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	northeast(t_data *data)
{
	if (data->temp->previous_x && data->temp->current_x \
	>= data->temp->previous_x && data->temp->current_y \
	<= data->temp->previous_y)
		return (1);
	else
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
	else
		return (0);
}

int	northwest(t_data *data)
{
	if (data->temp->previous_x && data->temp->current_x <= \
		data->temp->previous_x && data->temp->current_y <= \
		data->temp->previous_y)
		return (1);
	else
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
	else
		return (0);
}

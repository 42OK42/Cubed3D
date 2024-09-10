/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:48:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 19:23:59 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	north_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = hit_y_int / data->settings->tile_size;
	x_tile = hit_x_int / data->settings->tile_size;
	if ((data->map[y_tile -1][x_tile -1] == '1' && \
		data->map[y_tile -1][x_tile] == '1') && \
		(data->map[y_tile][x_tile -1] == '0' && \
		data->map[y_tile][x_tile] == '0' )
		)
		return (1);
	else
		return (0);
}

int	south_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = hit_y_int / data->settings->tile_size;
	x_tile = hit_x_int / data->settings->tile_size;
	if ((data->map[y_tile -1][x_tile -1] == '0' && \
		data->map[y_tile -1][x_tile] == '0') && \
		(data->map[y_tile][x_tile -1] == '1' && \
		data->map[y_tile][x_tile] == '1' ))
		return (1);
	else
		return (0);
}

int	east_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = hit_y_int / data->settings->tile_size;
	x_tile = hit_x_int / data->settings->tile_size;
	if ((data->map[y_tile -1][x_tile -1] == '1' && \
		data->map[y_tile -1][x_tile] == '0') && \
		(data->map[y_tile][x_tile -1] == '1' && \
		data->map[y_tile][x_tile] == '0' ))
		return (1);
	else
		return (0);
}

int	west_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = hit_y_int / data->settings->tile_size;
	x_tile = hit_x_int / data->settings->tile_size;
	if ((data->map[y_tile -1][x_tile -1] == '0' && \
		data->map[y_tile -1][x_tile] == '1') && \
		(data->map[y_tile][x_tile -1] == '0' && \
		data->map[y_tile][x_tile] == '1'))
		return (1);
	else
		return (0);
}

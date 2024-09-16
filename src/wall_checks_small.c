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

int	south_wall(t_data *data, long double hit_x_f, int hit_y_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = hit_y_int / data->settings->tile_size;
	x_tile = (int)hit_x_f / data->settings->tile_size;
	if (data->map[y_tile -1][x_tile] == '1' && \
		ft_strchr("0NSEW", data->map[y_tile][x_tile]))
		return (1);
	else
		return (0);
}

int	north_wall(t_data *data, long double hit_x_f, int hit_y_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = hit_y_int / data->settings->tile_size;
	x_tile = (int)hit_x_f / data->settings->tile_size;
	if (ft_strchr("0NSEW", data->map[y_tile -1][x_tile]) && \
		data->map[y_tile][x_tile] == '1' )
		return (1);
	else
		return (0);
}

int	east_wall(t_data *data, long double hit_y_f, int hit_x_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = (int)hit_y_f / data->settings->tile_size;
	x_tile = hit_x_int / data->settings->tile_size;
	if (ft_strchr("0NSEW", data->map[y_tile][x_tile -1]) && \
		data->map[y_tile][x_tile] == '1' )
		return (1);
	else
		return (0);
}

int	west_wall(t_data *data, long double hit_y_f, int hit_x_int)
{
	int	y_tile;
	int	x_tile;

	y_tile = 0;
	x_tile = 0;
	y_tile = (int)hit_y_f / data->settings->tile_size;
	x_tile = hit_x_int / data->settings->tile_size;
	if (data->map[y_tile][x_tile -1] == '1' && \
		ft_strchr("0NSEW", data->map[y_tile][x_tile]))
		return (1);
	else
		return (0);
}

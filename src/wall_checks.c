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

int north_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	if((data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size-1] == '1' &&
		data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size] == '1') && \
		 (data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size -1] == '0' && \
		 data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size] == '0' )
		)
		return (1);
	else
		return (0);
}


int south_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	if((data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size-1] == '0' &&
		data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size] == '0') && \
		(data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size -1] == '1' && \
		data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size] == '1' ))
		return (1);
	else
		return (0);
}

int west_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	if((data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size-1] == '1' &&
		data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size] == '0') &&  \
		(data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size -1] == '1' && \
		data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size] == '0' ))
		return (1);
	else
		return (0);
}

int east_wall_crossing(t_data *data, int hit_x_int, int hit_y_int)
{
	if((data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size-1] == '0' &&
		data->map[hit_y_int/data->settings->tile_size-1][hit_x_int/data->settings->tile_size] == '1') && \
		(data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size -1] == '0' && \
		data->map[hit_y_int/data->settings->tile_size][hit_x_int/data->settings->tile_size] == '1' ))
		return (1);
	else
		return (0);
}

int north_wall(t_data *data, long double hit_x_f, int hit_y_int)
{
	if((data->map[hit_y_int/data->settings->tile_size-1][(int)hit_x_f/data->settings->tile_size] == '1' &&
		 data->map[hit_y_int/data->settings->tile_size][(int)hit_x_f/data->settings->tile_size] == '0' ))
		return (1);
	else
		return (0);
}

int south_wall(t_data *data, long double hit_x_f, int hit_y_int)
{
	if((data->map[hit_y_int/data->settings->tile_size-1][(int)hit_x_f/data->settings->tile_size] == '0' &&
		 data->map[hit_y_int/data->settings->tile_size][(int)hit_x_f/data->settings->tile_size] == '1' ))
		return (1);
	else
		return (0);
}

int east_wall(t_data *data, long double hit_y_f, int hit_x_int)
{
	if((data->map[(int)hit_y_f/data->settings->tile_size][hit_x_int/data->settings->tile_size-1] == '0' &&
		 data->map[(int)hit_y_f/data->settings->tile_size][hit_x_int/data->settings->tile_size] == '1' ))
		return (1);
	else
		return (0);
}

int west_wall(t_data *data, long double hit_y_f, int hit_x_int)
{
	if((data->map[(int)hit_y_f/data->settings->tile_size][hit_x_int/data->settings->tile_size-1] == '1' &&
		 data->map[(int)hit_y_f/data->settings->tile_size][hit_x_int/data->settings->tile_size] == '0' ))
		return (1);
	else
		return (0);
}
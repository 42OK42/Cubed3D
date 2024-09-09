/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:45:51 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 15:45:54 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

long double	adjust_towards_closest_multiple_by(long double current_x, \
							long double tile_size, long double inch)
{
	long double	closest_multiple;
	long double	addition_result;
	long double	subtraction_result;
	long double	dist_addition;
	long double	dist_subtraction;

	closest_multiple = closest_multiple_of_tile(current_x, tile_size);
	addition_result = inch * (current_x + closest_multiple);
	subtraction_result = inch * (current_x - closest_multiple);
	dist_addition = fabs((double)(closest_multiple - addition_result));
	dist_subtraction = fabs((double)(closest_multiple - subtraction_result));
	if (dist_addition < dist_subtraction)
		return (addition_result);
	else
		return (subtraction_result);
}

long double	middle_value(long double a, long double b)
{
	return ((a + b) / 2.0L);
}

void	init_ray_values(t_data *data, long double ray_angle)
{
	data->temp->current_x = data->player->player_position[0][0];
	data->temp->current_y = data->player->player_position[0][1];
	data->temp->previous_x = data->player->player_position[0][0];
	data->temp->previous_y = data->player->player_position[0][1];
	if (ray_angle != 0)
	{
		data->temp->step_x = cos((ray_angle - 90) * M_PI / 180.0) \
		* data->settings->ray_step_size;
		data->temp->step_y = sin((ray_angle - 90) * M_PI / 180.0) \
		* data->settings->ray_step_size;
	}
	else
	{
		data->temp->step_x = 0;
		data->temp->step_y = -data->settings->ray_step_size;
	}
}

void	update_ray_position(t_data *data, int j)
{
	long double	scale;

	scale = 1e5;
	data->temp->current_x = (data->player->player_position[0][0] \
	* scale + j * data->temp->step_x * scale) / scale;
	data->temp->current_y = (data->player->player_position[0][1] \
	* scale + j * data->temp->step_y * scale) / scale;
}

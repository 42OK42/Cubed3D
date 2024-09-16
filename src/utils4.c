/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:45:44 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 15:45:47 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	calculate_image_x(t_data *data, int ray_id, int image_width)
{
	if ((int)data->rays[ray_id]->hit_x % data->settings->tile_size == 0)
		return (((int)data->rays[ray_id]->hit_y % data->settings->tile_size) \
			* image_width / data->settings->tile_size);
	else
		return (((int)data->rays[ray_id]->hit_x % data->settings->tile_size) \
			* image_width / data->settings->tile_size);
}

t_point	*backtrack_to_x(t_data *data)
{
	t_point		*ret;
	long double	y_mov_for_x;
	long double	x_diff;

	ret = ft_calloc(sizeof(t_point), 1);
	if (data->temp->step_x == 0)
	{
		if (ret != NULL)
			free(ret);
		ret = NULL;
		return (ret);
	}
	y_mov_for_x = data->temp->step_y / data->temp->step_x;
	x_diff = absolute_difference(data->temp->current_x, \
		closest_multiple_of_tile(data->temp->current_x, \
		data->settings->tile_size));
	ret->x = closest_multiple_of_tile(data->temp->current_x, \
		data->settings->tile_size);
	if (closest_multiple_of_tile(data->temp->current_x, \
		data->settings->tile_size) >= data->temp->current_x)
		ret->y = data->temp->current_y + (y_mov_for_x * x_diff);
	if (closest_multiple_of_tile(data->temp->current_x, \
		data->settings->tile_size) <= data->temp->current_x)
		ret->y = data->temp->current_y - (y_mov_for_x * x_diff);
	return (ret);
}

t_point	*backtrack_to_y(t_data *data)
{
	t_point		*ret;
	long double	x_mov_for_y;
	long double	y_diff;

	ret = ft_calloc(sizeof(t_point), 1);
	if (data->temp->step_y == 0)
	{
		if (ret != NULL)
			free(ret);
		ret = NULL;
		return (ret);
	}
	x_mov_for_y = data->temp->step_x / data->temp->step_y;
	y_diff = absolute_difference(data->temp->current_y, \
		closest_multiple_of_tile(data->temp->current_y, \
			data->settings->tile_size));
	ret->y = closest_multiple_of_tile(data->temp->current_y, \
		data->settings->tile_size);
	if (closest_multiple_of_tile(data->temp->current_y, \
		data->settings->tile_size) >= data->temp->current_y)
		ret->x = data->temp->current_x + (x_mov_for_y * y_diff);
	if (closest_multiple_of_tile(data->temp->current_y, \
		data->settings->tile_size) <= data->temp->current_y)
		ret->x = data->temp->current_x - (x_mov_for_y * y_diff);
	return (ret);
}

int	xor(int a, int b)
{
	if (a == 1 && b == 0)
		return (1);
	else if (a == 0 && b == 1)
		return (1);
	else
		return (0);
}

int	neither_in_range(t_data *data)
{
	if (data->temp->d_curr_x >= data->settings->ray_step_size && \
	data->temp->d_curr_y >= data->settings->ray_step_size)
	{
		data->temp->current_x = adjust_towards_closest_multiple_by \
		(data->temp->previous_x, data->temp->current_x, 0.0004);
		data->temp->current_y = adjust_towards_closest_multiple_by \
		(data->temp->previous_y, data->temp->current_y, 0.0004);
		return (1);
	}
	else 
		return (0);
}

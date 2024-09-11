/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/16 16:22:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	early_return(t_data *data, t_point *ret)
{
	if (neither_in_range(data))
		return (0);
	if (xor(data->temp->d_curr_x <= data->settings->ray_step_size * 1, \
			data->temp->d_curr_y <= data->settings->ray_step_size * 1))
	{
		if (data->temp->d_curr_x < data->temp->d_curr_y)
		{
			ret->x = data->temp->sect_with_x->x;
			ret->y = data->temp->sect_with_x->y;
		}
		if (data->temp->d_curr_x > data->temp->d_curr_y)
		{
			ret->x = data->temp->sect_with_y->x;
			ret->y = data->temp->sect_with_y->y;
		}
		return (1);
	}
	ret->x = data->temp->current_x;
	ret->y = data->temp->current_y;
	return (0);
}

int	ns_hit(t_data *data, t_point *ret)
{
	if (data->temp->d_curr_x <= data->settings->ray_step_size && \
	data->temp->d_start_x <= data->temp->d_start_y \
	&& ((\
	north_wall(data, data->temp->sect_with_x->x, \
	(int)data->temp->sect_with_x->y)) || (south_wall(data, \
	data->temp->sect_with_x->x, (int)data->temp->sect_with_x->y))))
	{
		ret->x = data->temp->sect_with_x->x;
		ret->y = data->temp->sect_with_x->y;
		if (data->temp->d_curr_y <= (data->settings->ray_step_size * 1) && \
		data->temp->d_start_y <= data->temp->d_start_x && \
		((data->temp->start->x < data->temp->sect_with_y->x && \
		east_wall(data, data->temp->sect_with_y->y, \
		(int)data->temp->sect_with_y->x)) || (data->temp->start->x > \
		data->temp->sect_with_y->x && west_wall(data, \
		data->temp->sect_with_y->y, (int)data->temp->sect_with_y->x))))
		{
			ret->x = data->temp->sect_with_y->x;
			ret->y = data->temp->sect_with_y->y;
		}
		return (1);
	}
	return (0);
}

int	ew_hit(t_data *data, t_point *ret)
{
	if (data->temp->d_curr_y <= data->settings->ray_step_size && \
	data->temp->d_start_y <= data->temp->d_start_x \
	&& ((data->temp->start->x < data->temp->sect_with_y->x && east_wall(data, \
	data->temp->sect_with_y->y, (int)data->temp->sect_with_y->x)) || \
	(data->temp->start->x > data->temp->sect_with_y->x && west_wall(data, \
	data->temp->sect_with_y->y, (int)data->temp->sect_with_y->x))))
	{
		ret->x = data->temp->sect_with_y->x;
		ret->y = data->temp->sect_with_y->y;
		if (data->temp->d_curr_x <= (data->settings->ray_step_size * 1) && \
		data->temp->d_start_x <= data->temp->d_start_y && \
		((data->temp->start->y > data->temp->sect_with_x->y && \
		north_wall(data, data->temp->sect_with_x->x, \
		(int)data->temp->sect_with_x->y)) || (data->temp->start->y \
		< data->temp->sect_with_x->y && south_wall(data, \
		data->temp->sect_with_x->x, (int)data->temp->sect_with_x->y))))
		{
			ret->x = data->temp->sect_with_x->x;
			ret->y = data->temp->sect_with_x->y;
		}
		return (1);
	}
	return (0);
}

void	calc_stuff(t_data *data, t_point *curr)
{
	curr->x = data->temp->current_x;
	curr->y = data->temp->current_y;
	data->temp->sect_with_x = backtrack_to_y(data);
	data->temp->sect_with_y = backtrack_to_x(data);
	data->temp->d_start_x = distance(data->temp->start, \
	data->temp->sect_with_x);
	data->temp->d_start_y = distance(data->temp->start, \
	data->temp->sect_with_y);
	data->temp->d_curr_x = distance(curr, data->temp->sect_with_x);
	data->temp->d_curr_y = distance(curr, data->temp->sect_with_y);
}

t_point	*get_true_intersection(t_point *start, t_data *data, t_temp *temp)
{
	t_point		*ret;
	t_point		*curr;

	data->temp->start = start;
	ret = malloc(sizeof(t_point));
	curr = malloc(sizeof(t_point));
	data->temp->sect_with_x = NULL;
	data->temp->sect_with_y = NULL;
	curr->x = temp->current_x;
	curr->y = temp->current_y;
	calc_stuff(data, curr);
	free(curr);
	if (early_return(data, ret))
		return (ret);
	if (ns_hit(data, ret) || ew_hit(data, ret))
		return (ret);
	else
	{
		ret->x = temp->current_x;
		ret->y = temp->current_y;
	}
	return (ret);
}

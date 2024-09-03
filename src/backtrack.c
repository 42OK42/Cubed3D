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

long double	distance(t_point *start, t_point *end)
{
	if (start == NULL || end == NULL)
		return (1000);
	return (sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2)));
}

int closestMultipleOfTile(int num, int tile_size)
{
    int remainder = num % tile_size;

    if (remainder < tile_size / 2) {
        return num - remainder;
    } else {
        return num + (tile_size - remainder);
    }
}

long double absolute_difference(long double num1, long double num2)
{
    long double diff = num1 - num2;
    
    if (diff < 0) {
        diff = -diff;
    }
    
    return diff;
}

t_point	*backtrack_to_x(t_data *data)
{
	t_point *ret;
	long double	y_mov_for_x;
	long double	x_diff;

	ret = malloc(sizeof(t_point));
	if (data->temp->step_x == 0)
	{
		ret = NULL;
		return (ret);
	}
	y_mov_for_x = data->temp->step_y/data->temp->step_x;
	x_diff = absolute_difference(data->temp->current_x, closestMultipleOfTile(data->temp->current_x, data->settings->tile_size));
	ret->x = closestMultipleOfTile(data->temp->current_x, data->settings->tile_size);
	if (closestMultipleOfTile(data->temp->current_x, data->settings->tile_size) >= data->temp->current_x)
		ret->y = data->temp->current_y + (y_mov_for_x * x_diff);
	if (closestMultipleOfTile(data->temp->current_x, data->settings->tile_size) <= data->temp->current_x)
		ret->y = data->temp->current_y - (y_mov_for_x * x_diff);
	return (ret);
}

t_point	*backtrack_to_y(t_data *data)
{
	t_point *ret;
	long double	x_mov_for_y;
	long double	y_diff;

	ret = malloc(sizeof(t_point));
	if (data->temp->step_y == 0)
	{
		ret = NULL;
		return (ret);
	}
	x_mov_for_y = data->temp->step_x/data->temp->step_y;
	y_diff = absolute_difference(data->temp->current_y, closestMultipleOfTile(data->temp->current_y, data->settings->tile_size));
	ret->y = closestMultipleOfTile(data->temp->current_y, data->settings->tile_size);
	if (closestMultipleOfTile(data->temp->current_y, data->settings->tile_size) >= data->temp->current_y)
		ret->x = data->temp->current_x + (x_mov_for_y * y_diff);
	if (closestMultipleOfTile(data->temp->current_y, data->settings->tile_size) <= data->temp->current_y)
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
		return(0);
}

long double adjustTowardsClosestMultipleBy(long double current_x, long double tile_size, long double inch)
{
    long double closest_multiple = closestMultipleOfTile(current_x, tile_size);

    long double addition_result = inch * (current_x + closest_multiple);
    long double subtraction_result = inch  * (current_x - closest_multiple);
    long double dist_addition = fabs((double)(closest_multiple - addition_result));
    long double dist_subtraction = fabs((double)(closest_multiple - subtraction_result));
    if (dist_addition < dist_subtraction)
		return addition_result;
    else
		return subtraction_result;
}

long double middleValue(long double a, long double b)
{
    return (a + b) / 2.0L;
}

t_point	*get_true_intersection(t_point *start, t_data *data, t_temp *temp)
{
	long double	d_start_x;
	long double	d_start_y;
	long double	d_curr_x;
	long double	d_curr_y;
	t_point *sect_with_x;
	t_point	*sect_with_y;
	t_point *ret;
	t_point *curr;

	(void)start;
	ret = malloc(sizeof(t_point));
	curr = malloc(sizeof(t_point));
	curr->x = temp->current_x;
	curr->y = temp->current_y;
	sect_with_x = backtrack_to_y(data);
	sect_with_y = backtrack_to_x(data);
	d_start_x = distance(start, sect_with_x);
	d_start_y = distance(start, sect_with_y);
	d_curr_x = distance(curr, sect_with_x);
	d_curr_y = distance(curr, sect_with_y);



	free(curr);


	if (d_curr_x >= data->settings->ray_step_size && d_curr_y >= data->settings->ray_step_size) //neither in range
	{
		data->esc++;


		data->temp->current_x = middleValue(temp->previous_x, temp->current_x);
		data->temp->current_y = middleValue(temp->previous_y, temp->current_y);
		ret = get_true_intersection(start, data, temp);
		return (ret);
	}


	if(d_curr_x <= data->settings->ray_step_size * 1 || d_curr_y <= data->settings->ray_step_size * 1) //either in range
		data->count0++;
	if(xor(d_curr_x < data->settings->ray_step_size * 1, d_curr_y < data->settings->ray_step_size * 1)) // one in range
	{
		data->count1++;
		if(d_curr_x < d_curr_y)
		{
			ret->x = sect_with_x->x;
			ret->y = sect_with_x->y;
			return (ret);
		}
		if(d_curr_x > d_curr_y)
		{
			ret->x = sect_with_y->x;
			ret->y = sect_with_y->y;
			return (ret);
		}
		dprintf(2,"error\n");
	}

	if (d_curr_x <= data->settings->ray_step_size && d_start_x <= d_start_y && ((start->y > sect_with_x->y && north_wall(data, sect_with_x->x, (int)sect_with_x->y)) || (start->y < sect_with_x->y && south_wall(data, sect_with_x->x, (int)sect_with_x->y)))) //
	{
		ret->x = sect_with_x->x;
		ret->y = sect_with_x->y;
		if (d_curr_y <= (data->settings->ray_step_size * 1) && d_start_y <= d_start_x && ((start->x < sect_with_y->x && east_wall(data, sect_with_y->y, (int)sect_with_y->x)) || (start->x > sect_with_y->x && west_wall(data, sect_with_y->y, (int)sect_with_y->x))))
		{
			ret->x = sect_with_y->x;
			ret->y = sect_with_y->y;
		}
	}
	else if(d_curr_y <= data->settings->ray_step_size && d_start_y <= d_start_x && ((start->x < sect_with_y->x && east_wall(data, sect_with_y->y, (int)sect_with_y->x)) || (start->x > sect_with_y->x && west_wall(data, sect_with_y->y, (int)sect_with_y->x))))
	{
		ret->x = sect_with_y->x;
		ret->y = sect_with_y->y;
		if (d_curr_x <= (data->settings->ray_step_size * 1) && d_start_x <= d_start_y && ((start->y > sect_with_x->y && north_wall(data, sect_with_x->x, (int)sect_with_x->y)) || (start->y < sect_with_x->y && south_wall(data, sect_with_x->x, (int)sect_with_x->y))))
		{
			ret->x = sect_with_x->x;
			ret->y = sect_with_x->y;
		}
	}
	else
	{
		ret->x = temp->current_x;
		ret->y = temp->current_y;

	}
		return (ret);
}
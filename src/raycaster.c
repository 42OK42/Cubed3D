/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/22 16:54:02 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	raycaster(t_data *data)
{
	int		i;
	float	fov;
	float	angle_step;
	float	start_angle;
	float	angle;

	i = 0;
	fov = data->settings->fov;
	angle_step = fov / (float)data->settings->num_rays;
	start_angle = data->player->player_direction - (fov / 2.0);

	while (i < data->settings->num_rays)
	{
		data->temp->hit_wall = 0;
		angle = start_angle + (i * angle_step);
		data->rays[i]->angle = angle;
		cast_ray(data, angle, i);
		i++;
	}
}

void	init_ray_values(t_data *data, float ray_angle)
{
	data->temp->current_x = data->player->player_position[0][0];
	data->temp->current_y = data->player->player_position[0][1];

	if (ray_angle != 0)
	{
		data->temp->step_x = cos((ray_angle - 90) * M_PI / 180.0) * data->settings->ray_step_size;
		data->temp->step_y = sin((ray_angle - 90) * M_PI / 180.0) * data->settings->ray_step_size;
	}
	else
	{
		data->temp->step_x = 0;
		data->temp->step_y = -data->settings->ray_step_size;
	}
}


void	update_ray_position(t_data *data)
{
	data->temp->current_x += data->temp->step_x;
	data->temp->current_y += data->temp->step_y;
}

int	check_wall_hit(t_data *data)
{
	int	cell_x;
	int	cell_y;

	cell_y = (int)((data->temp->current_y) / data->settings->tile_size);
	cell_x = (int)(data->temp->current_x / data->settings->tile_size);
	if (data->temp->previous_x && data->temp->current_x >= data->temp->previous_x && data->temp->current_y >= data->temp->previous_y)
	{
		if ((int)data->temp->current_x % data->settings->tile_size == 0 && (int)data->temp->current_y % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x-1] == '1' && data->map[cell_y - 1][cell_x])
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	else if (data->temp->previous_x && data->temp->current_x <= data->temp->previous_x && data->temp->current_y >= data->temp->previous_y)
	{
		if (((int)data->temp->current_x + 1) % data->settings->tile_size == 0 && (int)data->temp->current_y % data->settings->tile_size == 0)
		{
			if (data->map[cell_y-1][cell_x] == '1' && data->map[cell_y][cell_x + 1] == '1')
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	else if (data->temp->previous_x && data->temp->current_x >= data->temp->previous_x && data->temp->current_y <= data->temp->previous_y)
	{
		if ((int)data->temp->current_x  % data->settings->tile_size == 0 && ((int)data->temp->current_y + 1) % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x-1] == '1' && data->map[cell_y + 1][cell_x])
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	else if (data->temp->previous_x && data->temp->current_x <= data->temp->previous_x && data->temp->current_y <= data->temp->previous_y)
	{
		if (((int)data->temp->current_x + 1) % data->settings->tile_size == 0 && ((int)data->temp->current_y + 1) % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x+1] == '1' && data->map[cell_y + 1][cell_x])
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	data->temp->previous_x = data->temp->current_x;
	data->temp->previous_y = data->temp->current_y;
	if (data->map[cell_y][cell_x] == '1')
	{
		data->temp->hit_wall = 1;
		return (1);
	}
	return (0);
}


void	cast_ray(t_data *data, float ray_angle, int i)
{
	int		j;
	float	start_x;
	float	start_y;
	float	distance;

	j = 0;
	start_x = data->player->player_position[0][0];
	start_y = data->player->player_position[0][1];
	init_ray_values(data, ray_angle);
	while (!data->temp->hit_wall)
	{
		update_ray_position(data);
		if (check_wall_hit(data))
		{
			distance = sqrt(pow(data->temp->current_x - start_x, 2) + pow(data->temp->current_y - start_y, 2));
			data->rays[i]->length = distance;
			data->rays[i]->hit_x = data->temp->current_x;
			data->rays[i]->hit_y = data->temp->current_y;
		}
		j++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 18:21:12 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	raycaster(t_data *data)
{
	int		i;
	float	fov;
	float	angle;

	i = 0;
	fov = data->settings->fov;
	while (i < data->settings->num_rays)
	{
		data->temp->hit_wall = 0;
		angle = data->player->player_direction - (fov / 2.0) + (fov * i / (float)data->settings->num_rays);
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
	int	cell_x2;
	int	cell_y2;

	cell_y = (int)((data->temp->current_y) / data->settings->tile_size);
	cell_x = (int)(data->temp->current_x / data->settings->tile_size);
	if ((int)data->temp->current_x % data->settings->tile_size < 1 && (int)data->temp->current_y % data->settings->tile_size < 1)
	{
		cell_x2 = cell_x - 1;
		cell_y2 = cell_y;
		if (data->map[cell_y2][cell_x2] == '1')
		{
			data->temp->hit_wall = 1;
			return (1);
		}
	}
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
	//printf("start_x: %f\n", start_x);
	start_y = data->player->player_position[0][1];
	//printf("start_y: %f\n", start_y);
	init_ray_values(data, ray_angle);
	//printf("ray_angle: %f\n", ray_angle);
	//printf("player_direction: %d\n", data->player->player_direction);
	while (!data->temp->hit_wall)
	{
		//printf("current_x_before_update: %f\n", data->temp->current_x);
		//printf("current_y_before_update: %f\n", data->temp->current_y);
		update_ray_position(data);
		//printf("current_x: %f\n", data->temp->current_x);
		//printf("current_y: %f\n", data->temp->current_y);
		if (check_wall_hit(data))
		{
			//printf("hit_x: %d\n", (int)data->temp->current_x);
			//printf("hit_y: %d\n", (int)data->temp->current_y);
			//printf("player_x: %d\n", data->player->player_position[0][0]);
			//printf("player_y: %d\n", data->player->player_position[0][1]);
			//printf("angle: %f\n", ray_angle);
			//printf("step_x: %f\n", data->temp->step_x);
			//printf("step_y: %f\n", data->temp->step_y);
			distance = sqrt(pow(data->temp->current_x - start_x, 2) + pow(data->temp->current_y - start_y, 2));
			//printf("distance: %f\n", distance);
			data->rays[i]->length = distance;
			data->rays[i]->hit_x = data->temp->current_x;
			data->rays[i]->hit_y = data->temp->current_y;
		}
		j++;
	}
}

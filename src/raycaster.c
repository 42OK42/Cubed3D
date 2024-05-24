/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/24 15:39:38 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	raycaster(t_data *data)
{
	int	i;
	int	fov;

	fov = data->settings->fov;
	i = 0;
	while (i < data->settings->num_rays)
	{
		data->rays[i]->angle = data->player->player_direction - (fov / 2) + (fov * i / data->settings->num_rays);
		calculate_distance_to_wall(data, data->rays[i]->angle, i);
		i++;
	}
}

void	calculate_distance_to_wall(t_data *data, int ray_angle, int i)
{
	data->temp->current_x = data->player->player_position[0][0];
	data->temp->current_y = data->player->player_position[0][1];
	data->temp->hit_wall = 0;
	data->temp->ray_angle_rad = ray_angle * M_PI / 180.0;
	data->temp->step_x = data->settings->ray_step_size * sin(data->temp->ray_angle_rad);
	data->temp->step_y = data->settings->ray_step_size * cos(data->temp->ray_angle_rad);

	while (!data->temp->hit_wall)
	{
		data->temp->next_x = round(data->temp->current_x + data->temp->step_x);
		data->temp->next_y = round(data->temp->current_y + data->temp->step_y);
		if (data->map[data->temp->next_y / data->settings->tile_size][data->temp->next_x / data->settings->tile_size] == '1')
		{
			data->temp->hit_wall = 1;
			data->rays[i]->length = sqrt(pow(data->temp->next_x - data->temp->current_x, 2) + pow(data->temp->next_y - data->temp->current_y, 2));
			printf("length: %f\n", data->rays[i]->length);
			data->rays[i]->hit_x = (int)data->temp->next_x;
			data->rays[i]->hit_y = (int)data->temp->next_y;
		}
		else
		{
			data->temp->current_x = data->temp->next_x;
			data->temp->current_y = data->temp->next_y;
		}
	}
}

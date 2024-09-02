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

void	raycaster(t_data *data)
{
	int		i;
	long double	fov;
	long double	angle;

	i = 0;
	fov = data->settings->fov;
	system("clear");
	printf("rays||||||||||||||||||||||||||||||||||||||\n");
	while (i < data->settings->num_rays)
	{
		data->temp->hit_wall = 0;
		angle = data->player->player_direction - (fov / 2.0) + (fov * i / (long double)data->settings->num_rays);
		data->rays[i]->angle = angle;
		cast_ray(data, angle, i);
		i++;
	}
	printf("\n");
}


void	cast_ray(t_data *data, long double ray_angle, int i)
{
	int		j;
	long double	distance;
	t_point *start;
	t_point *true_sect;

	true_sect = malloc(sizeof(t_point));
	start = malloc(sizeof(t_point));
	j = 0;
	start->x = data->player->player_position[0][0];
	start->y = data->player->player_position[0][1];
	init_ray_values(data, ray_angle);
	while (!data->temp->hit_wall)
	{
		update_ray_position(data);
		if (check_wall_hit(data))
		{
			true_sect = get_true_intersection(start, data, data->temp);
			data->temp->current_x = true_sect->x;
			data->temp->current_y = true_sect->y;
			distance = sqrt(pow(data->temp->current_x - start->x, 2) + pow(data->temp->current_y - start->y, 2));
			data->rays[i]->length = distance;
			data->rays[i]->hit_x = data->temp->current_x;
			data->rays[i]->hit_y = data->temp->current_y;
		}
		j++;
	}
}

void	init_ray_values(t_data *data, long double ray_angle)
{
	data->temp->current_x = data->player->player_position[0][0];
	data->temp->current_y = data->player->player_position[0][1];
	data->temp->previous_x = data->player->player_position[0][0]; // for safety, maybe unecessary
	data->temp->previous_y = data->player->player_position[0][1]; // for safety, maybe unecessary
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

	cell_y = ((int)(data->temp->current_y) / data->settings->tile_size);
	cell_x = ((int)(data->temp->current_x) / data->settings->tile_size);
	if (data->temp->previous_x && data->temp->current_x >= data->temp->previous_x && data->temp->current_y >= data->temp->previous_y)
	{
		if ((int)data->temp->current_x % data->settings->tile_size == 0 && (int)data->temp->current_y % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x-1] == '1' && data->map[cell_y - 1][cell_x] == '1')
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
			if (data->map[cell_y][cell_x-1] == '1' && data->map[cell_y + 1][cell_x] == '1')
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
			if (data->map[cell_y][cell_x+1] == '1' && data->map[cell_y + 1][cell_x] == '1')
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

long double	find_closest_x(t_data *data)
{
	long double	closest_grid_section;
	int		grid_num;

	grid_num = ((int)data->temp->current_x + 1) / data->settings->tile_size;
	closest_grid_section = grid_num * data->settings->tile_size;
	return(closest_grid_section);
}

long double find_closest_multiple(long double x, int t) 
{
    long double closest_multiple = round(x / t) * t;
    return closest_multiple;
}
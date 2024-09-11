/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 15:08:33 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/cubed3D.h"

void	raycaster(t_data *data)
{
	int			i;
	long double	fov;
	long double	angle;

	i = 0;
	fov = data->settings->fov;
	while (i < data->settings->num_rays)
	{
		data->temp->hit_wall = 0;
		angle = data->player->player_direction - (fov / 2.0) \
			+ (fov * i / (long double)data->settings->num_rays);
		data->rays[i]->angle = angle;
		cast_ray(data, angle, i);
		i++;
		// free_ray_loop(data);
	}
}

void	ray_loop(t_data *data, t_point *true_sect, int i, int *j)
{
	long double	distance;

	update_ray_position(data, (*j));
	if (check_wall_hit(data))
	{
		true_sect = get_true_intersection(data->temp->start, data, data->temp);
		data->temp->current_x = true_sect->x;
		data->temp->current_y = true_sect->y;
		distance = sqrt(pow(data->temp->current_x - data->temp->start->x, 2) \
		+ pow(data->temp->current_y - data->temp->start->y, 2));
		data->rays[i]->length = distance;
		data->rays[i]->hit_x = data->temp->current_x;
		data->rays[i]->hit_y = data->temp->current_y;
		free_ray_loop(data);
		free(true_sect);
	}
	(*j)++;
}

void	cast_ray(t_data *data, long double ray_angle, int i)
{
	int			j;
	t_point		*true_sect;

	true_sect = NULL;
	j = 0;
	data->temp->start = malloc(sizeof(t_point));
	data->temp->start->x = data->player->player_position[0][0];
	data->temp->start->y = data->player->player_position[0][1];
	init_ray_values(data, ray_angle);
	while (!data->temp->hit_wall)
		ray_loop(data, true_sect, i, &j);
	free(data->temp->start);
}

int	check_wall_hit(t_data *data)
{
	int	cell_x;
	int	cell_y;

	cell_y = ((int)(data->temp->current_y) / data->settings->tile_size);
	cell_x = ((int)(data->temp->current_x) / data->settings->tile_size);
	if ((southeast(data) && southeast_corner(data, cell_x, cell_y)) || \
		(southwest(data) && southwest_corner(data, cell_x, cell_y)) || \
		(southeast(data) && southeast_corner(data, cell_x, cell_y)) || \
		(southwest(data) && southwest_corner(data, cell_x, cell_y)))
	{
		data->temp->hit_wall = 1;
		return (1);
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

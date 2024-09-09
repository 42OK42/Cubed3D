/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:39:54 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 16:44:06 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	case_corner(t_data *data, int hit_x_int, int hit_y_int, int ray_id)
{
	if ((fmod(data->rays[ray_id]->hit_y, \
	(double)data->settings->tile_size) == 0) && \
		(fmod(data->rays[ray_id]->hit_x, \
	(double)data->settings->tile_size) == 0))
	{
		if (north_wall_crossing(data, hit_x_int, hit_y_int))
			return (data->assets->wall_north);
		if (south_wall_crossing(data, hit_x_int, hit_y_int))
			return (data->assets->wall_south);
		if (west_wall_crossing(data, hit_x_int, hit_y_int))
			return (data->assets->wall_west);
		if (east_wall_crossing(data, hit_x_int, hit_y_int))
			return (data->assets->wall_east);
	}
}

int	**get_right_image(t_data *data, int ray_id)
{
	int			hit_x_int;
	int			hit_y_int;
	long double	player_y;
	long double	player_x;

	hit_x_int = (int)round(data->rays[ray_id]->hit_x);
	hit_y_int = (int)round(data->rays[ray_id]->hit_y);
	player_y = data->player->player_position[0][1];
	player_x = data->player->player_position[0][0];
	case_corner(data, hit_x_int, hit_y_int, ray_id);
	if ((fmod(data->rays[ray_id]->hit_y, \
	(double)data->settings->tile_size) == 0) \
	&& (fmod(data->rays[ray_id]->hit_x, \
	(double)data->settings->tile_size) != 0))
		return (get_image_for_horizontal_hit(data, hit_y_int, player_y));
	if ((fmod(data->rays[ray_id]->hit_x, \
	(double)data->settings->tile_size) == 0) \
	&& (fmod(data->rays[ray_id]->hit_y, \
	(double)data->settings->tile_size) != 0))
		return (get_image_for_vertical_hit(data, hit_x_int, player_x));
	if (data->temp->previous_image != NULL)
		return (data->temp->previous_image);
	return (data->assets->wall_sectfail);
}

int	**get_image_for_vertical_hit(t_data *data, \
		int hit_x_int, long double player_x)
{
	if (player_x < hit_x_int)
	{
		return (data->assets->wall_west);
	}
	if (player_x > hit_x_int)
	{
		return (data->assets->wall_east);
	}
	return (NULL);
}

int	**get_image_for_horizontal_hit(t_data *data, \
			int hit_y_int, long double player_y)
{
	if (player_y < hit_y_int)
	{
		return (data->assets->wall_south);
	}
	if (player_y > hit_y_int)
	{
		return (data->assets->wall_north);
	}
	return (NULL);
}

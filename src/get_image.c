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

int	**get_right_image(t_data *data, int ray_id)
{
	int		hit_x_int;
	int		hit_y_int;
	float	player_y;

	hit_x_int = (int)round(data->rays[ray_id]->hit_x);
	hit_y_int = (int)round(data->rays[ray_id]->hit_y);
	player_y = data->player->player_position[0][1];
	if ((hit_x_int % data->settings->tile_size) == 0)
		return (get_image_for_vertical_hit(data, \
			hit_x_int, hit_y_int));
	if ((hit_y_int % data->settings->tile_size) == 0)
		return (get_image_for_horizontal_hit(data, hit_y_int, player_y));
	return (NULL);
}

int	**get_image_for_vertical_hit(t_data *data, int hit_x_int, int hit_y_int)
{
	float	player_x;
	float	player_y;

	player_x = data->player->player_position[0][0];
	player_y = data->player->player_position[0][1];
	if (hit_y_int % data->settings->tile_size == 0)
	{
		if (player_y < hit_y_int && player_x < hit_x_int)
			return (data->assets->wall_north);
		if (player_y < hit_y_int && player_x > hit_x_int)
			return (data->assets->wall_east);
		if (player_y > hit_y_int && player_x < hit_x_int)
			return (data->assets->wall_west);
		if (player_y > hit_y_int && player_x > hit_x_int)
			return (data->assets->wall_south);
	}
	else
	{
		if (player_x < hit_x_int)
			return (data->assets->wall_west);
		if (player_x > hit_x_int)
			return (data->assets->wall_east);
	}
	return (NULL);
}

int	**get_image_for_horizontal_hit(t_data *data, int hit_y_int, float player_y)
{
	if (player_y < hit_y_int)
		return (data->assets->wall_north);
	if (player_y > hit_y_int)
		return (data->assets->wall_south);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:22 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 17:38:53 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	draw_minimap(t_data *data)
{
	draw_element(data, '1', data->settings->wall_color);
	draw_element(data, ' ', data->settings->space_color);
	draw_element(data, '0', data->settings->background_color);
	draw_element(data, 'N', data->settings->background_color);
	draw_element(data, 'S', data->settings->background_color);
	draw_element(data, 'E', data->settings->background_color);
	draw_element(data, 'W', data->settings->background_color);
	draw_player(data);
	draw_rays(data);
}

void	draw_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->settings->num_rays)
	{
		draw_ray(data, data->rays[i]->length, data->rays[i]->angle);
		i++;
	}
}

void	draw_ray(t_data *data, float length, int angle)
{
	data->temp->angle_rad = (angle - 90) * M_PI / 180.0;
	data->temp->center_x = data->player->player_position[0][0];
	data->temp->center_y = data->player->player_position[0][1];
	calculate_end_point(data, round(length));
	bresenham_algorithm(data);
}

void	draw_player(t_data *data)
{
	int	px;
	int	py;
	int	offset;
	int	i;
	int	j;

	px = (int)(data->player->player_position[0][0]);
	py = (int)(data->player->player_position[0][1]);
	offset = 5;
	i = px - offset;
	while (i <= px + offset)
	{
		j = py - offset;
		while (j <= py + offset)
		{
			mlx_pixel_put(data->mlx->mlx, data->mlx->mlx_win_minimap, i, \
				j, data->settings->player_color);
			j++;
		}
		i++;
	}
}

void	draw_element(t_data *data, char c, int c_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == c)
				draw_tile(data, x * data->settings->tile_size, \
					y * data->settings->tile_size, c_color);
			x++;
		}
		y++;
	}
}

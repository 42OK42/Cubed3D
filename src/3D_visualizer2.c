/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:33:26 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 16:39:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

float	fix_fish_eye(t_data *data, int ray_id)
{
	float	player_angle_rad;
	float	ray_angle_rad;
	float	diff_angle;

	player_angle_rad = data->player->player_direction * M_PI / 180;
	ray_angle_rad = data->rays[ray_id]->angle * M_PI / 180 ;
	diff_angle = ray_angle_rad - player_angle_rad;
	while (diff_angle < -M_PI)
		diff_angle += 2 * M_PI;
	while (diff_angle > M_PI)
		diff_angle -= 2 * M_PI;
	return (data->rays[ray_id]->length * cos(diff_angle));
}

void	draw_background(t_data *data)
{
	draw_background_section(data, 0, data->settings->window_height / \
	2, data->settings->upper_background_color);
	draw_background_section(data, data->settings->window_height \
	/ 2, data->settings->window_height, data->settings->lower_background_color);
}

void	draw_background_section(t_data *data, int \
start_y, int end_y, unsigned int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < data->settings->window_width)
		{
			*(unsigned int *)(data->mlx->data_addr + \
				(y * data->mlx->size_line + x * \
				(data->mlx->bits_per_pixel / 8))) = color;
			x++;
		}
		y++;
	}
}

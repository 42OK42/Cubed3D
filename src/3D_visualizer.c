/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 19:54:46 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

/* void	draw_wall_slice(t_data *data, int x, int wall_height, int color)
{
	int	start_y;
	int	end_y;
	int	y;

	start_y = (data->settings->window_height / 2) - (wall_height / 2);
	//printf("start_y: %d\n", start_y);
	end_y = (data->settings->window_height / 2) + (wall_height / 2);
	//printf("end_y: %d\n", end_y);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= data->settings->window_height)
		end_y = data->settings->window_height - 1;
	y = start_y;
	while (y <= end_y)
	{
		mlx_pixel_put(data->mlx->mlx, data->mlx->mlx_win, x, y, color);
		y++;
	}
}

void	draw_3d_view(t_data *data)
{
	int		i;
	int		wall_height;
	int		screen_x;
	int		color;
	float	corrected_distance;

	i = 0;
	printf("draw_3d_view\n");
	while (i < data->settings->num_rays)
	{
		// Distance correction to avoid fish-eye effect
		corrected_distance = data->rays[i]->length * cos((data->rays[i]->angle - data->player->player_direction) * M_PI / 180);
		wall_height = (int)((data->settings->tile_size / corrected_distance) * data->settings->dist_to_proj_plane);
		//wall_height = (int)((data->settings->tile_size / data->rays[i]->length) * data->settings->dist_to_proj_plane);
		printf("ray[%i] wall_height: %d\n", i, wall_height);
		printf("data->rays[%i]->length: %f\n", i, data->rays[i]->length);
		//printf("data->rays[%i]->hit_x: %f\n", i, data->rays[i]->hit_x);
		//printf("data->rays[%i]->hit_y: %f\n", i, data->rays[i]->hit_y);
		//printf("corrected_distance: %f\n", corrected_distance);
		screen_x = (data->settings->window_width / data->settings->num_rays) * i;
		color = 0xFFFFFF;
		draw_wall_slice(data, screen_x, wall_height, color);
		i++;
	}
} */

void	draw_wall_slice(t_data *data, int x, int wall_height, int color)
{
	int	start_y;
	int	end_y;
	int	y;

	start_y = (data->settings->window_height / 2) - (wall_height / 2);
	end_y = (data->settings->window_height / 2) + (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= data->settings->window_height)
		end_y = data->settings->window_height - 1;
	y = start_y;
	while (y <= end_y)
	{
		mlx_pixel_put(data->mlx->mlx, data->mlx->mlx_win, x, y, color);
		y++;
	}
}

void	draw_3d_view(t_data *data)
{
	int		i;
	int		wall_height;
	int		screen_x;
	int		color;
	float	corrected_distance;
	int		prev_screen_x;

	i = 0;
	printf("draw_3d_view\n");
	while (i < data->settings->num_rays)
	{
		corrected_distance = data->rays[i]->length * cos((data->rays[i]->angle - data->player->player_direction) * M_PI / 180);
		wall_height = (int)((data->settings->tile_size / corrected_distance) * data->settings->dist_to_proj_plane);
		if (wall_height > data->settings->window_height)
			wall_height = data->settings->window_height;
		screen_x = (data->settings->window_width / data->settings->num_rays) * i;
		color = 0xFFFFFF;
		draw_wall_slice(data, screen_x, wall_height, color);
		if (i > 0)
		{
			;
			prev_screen_x = (data->settings->window_width / data->settings->num_rays) * (i - 1);
			fill_wall_between_rays(data, prev_screen_x, screen_x, wall_height, color);
		}
		i++;
	}
}

void	fill_wall_between_rays(t_data *data, int x0, int x1, int wall_height, int color)
{
	int	sign_x;

	if (x0 < x1)
		sign_x = 1;
	else
		sign_x = -1;

	while (x0 != x1 + sign_x)
	{
		draw_wall_slice(data, x0, wall_height, color);
		x0 += sign_x;
	}
}

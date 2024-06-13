/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/31 21:52:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

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

char ***get_right_image(t_data *data, int i)
{
	int hit_x_int = (int)round(data->rays[i]->hit_x);
	int hit_y_int = (int)round(data->rays[i]->hit_y);
	int tile_size = data->settings->tile_size;
	float player_x = data->player->player_position[0][0];
	float player_y = data->player->player_position[0][1];

	if ((hit_x_int % tile_size) == 0)
	{
		if (hit_y_int % tile_size == 0)
		{
			if (player_y < hit_y_int && player_x < hit_x_int)
				return ( data->assets->wall_north);
			if (player_y < hit_y_int && player_x > hit_x_int)
				return ( data->assets->wall_east);
			if (player_y > hit_y_int && player_x < hit_x_int)
				return ( data->assets->wall_west);
			if (player_y > hit_y_int && player_x > hit_x_int)
				return ( data->assets->wall_south);
		}
		else
		{
			if (player_x < hit_x_int)
				return ( data->assets->wall_west);
			if (player_x > hit_x_int)
				return ( data->assets->wall_east);
		}
	}
	if ((hit_y_int % tile_size) == 0)
	{
		if (player_y < hit_y_int)
			return (data->assets->wall_north);
		if (player_y > hit_y_int)
			return ( data->assets->wall_south);
	}
	return (NULL);
}

/* char ***get_right_image(t_data *data, int i)
{
	int hit_x_int = (int)round(data->rays[i]->hit_x);
	int hit_y_int = (int)round(data->rays[i]->hit_y);
	int tile_size = data->settings->tile_size;
	float player_x = data->player->player_position[0][0];
	float player_y = data->player->player_position[0][1];

	printf("hit_x_int %i hit_y_int %i\n", hit_x_int, hit_y_int);
	printf("player_x %f player_y %f\n", player_x, player_y);
	if ((hit_x_int % tile_size) == 0 && (int)player_x < hit_x_int)
	{
		if (!(hit_y_int % tile_size) == 0 && !(int)player_y < hit_y_int)
			return (printf("ray[%i] ray_hitx %f hit y %f hit wall_west\n", i, data->rays[i]->hit_x, data->rays[i]->hit_y), data->assets->wall_west);
	}
	else if ((hit_y_int % tile_size) == 0 && (int)player_y < hit_y_int && (int)player_x > hit_x_int)
		return (printf("ray[%i] ray_hitx %f hit y %f hit wall_north\n", i, data->rays[i]->hit_x, data->rays[i]->hit_y), data->assets->wall_north);
	else if ((hit_x_int % tile_size) == 0 && (int)player_x > hit_x_int && (int)player_y > hit_y_int)
		return (printf("ray[%i] ray_hitx %f hit y %f hit wall_east\n", i, data->rays[i]->hit_x, data->rays[i]->hit_y), data->assets->wall_east);
	else if ((hit_y_int % tile_size) == 0 && (int)player_y > hit_y_int && (int)player_x < hit_x_int)
		return (printf("ray[%i] ray_hitx %f hit y %f hit wall_south\n", i, data->rays[i]->hit_x, data->rays[i]->hit_y), data->assets->wall_south);
	ft_printf("no wall\n");
	return (NULL);
} */



void	draw_3d_view(t_data *data)
{
	int		i;
	int		wall_height;
	int		screen_x;
	int		color;
	float	corrected_distance;
	int		prev_screen_x;

	i = 0;
	while (i < data->settings->num_rays)
	{
		get_right_image(data, i);
		corrected_distance = data->rays[i]->length * cos((data->rays[i]->angle - data->player->player_direction) * M_PI / 180);
		wall_height = (int)((data->settings->tile_size / corrected_distance) * data->settings->dist_to_proj_plane);
		if (wall_height > data->settings->window_height)
			wall_height = data->settings->window_height;
		screen_x = (data->settings->window_width / data->settings->num_rays) * i;
		color = 0xFFFFFF;
		draw_wall_slice(data, screen_x, wall_height, color);
		if (i > 0)
		{
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

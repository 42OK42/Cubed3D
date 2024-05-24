/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:22 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/24 13:11:24 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/cubed3D.h"

void	draw_level(t_data *data, t_window *window)
{
	draw_element(data, window, '1', data->settings->wall_color);
	draw_element(data, window, '0', data->settings->background_color);
	draw_element(data, window, 'N', data->settings->background_color);
	draw_player(data, window);
	draw_ray(data, window, data->settings->direction_line_length, data->player->player_direction); // Player direction
}

void	draw_ray(t_data *data, t_window *window, float length, int angle)
{
	data->temp->angle_rad = (angle - 90) * M_PI / 180.0;
	data->temp->center_x = data->player->player_position[0][0];
	data->temp->center_y = data->player->player_position[0][1];
	calculate_end_point(data, length);
	bresenham_algorithm(data, window);
}

void	draw_player(t_data *data, t_window *window)
{
	int	px;
	int	py;
	int	offset;
	int	i;
	int	j;

	px = data->player->player_position[0][0];
	py = data->player->player_position[0][1];
	offset = 5;
	i = px - offset;
	while (i <= px + offset)
	{
		j = py - offset;
		while (j <= py + offset)
		{
			mlx_pixel_put(window->mlx, window->mlx_win, i, j, data->settings->player_color);
			j++;
		}
		i++;
	}
}

void	draw_element(t_data *data, t_window *window, char c, int c_color)
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
				draw_tile(window, data->settings->tile_size, x * data->settings->tile_size, y * data->settings->tile_size, c_color);
			x++;
		}
		y++;
	}
}

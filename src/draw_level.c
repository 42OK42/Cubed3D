/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_level.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:22 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/23 18:43:32 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/cubed3D.h"

void	draw_level(t_data *data, t_window *window)
{
	draw_element(data, window, '1', data->settings->wall_color);
	draw_element(data, window, '0', data->settings->background_color);
	draw_element(data, window, 'N', data->settings->background_color);
	draw_player(data, window);
	draw_player_direction(data, window);
}

void	calculate_end_point(t_data *data, int length)
{
	data->temp->end_x = data->temp->center_x + (int)(length * cos(data->temp->angle_rad));
	data->temp->end_y = data->temp->center_y + (int)(length * sin(data->temp->angle_rad));
}

void	bresenham_algorithm(t_data *data, t_window *window)
{
	int	e2;

	data->temp->dx = abs(data->temp->end_x - data->temp->center_x);
	data->temp->dy = -abs(data->temp->end_y - data->temp->center_y);
	if (data->temp->center_x < data->temp->end_x)
		data->temp->sx = 1;
	else
		data->temp->sx = -1;
	if (data->temp->center_y < data->temp->end_y)
		data->temp->sy = 1;
	else
		data->temp->sy = -1;
	data->temp->err = data->temp->dx + data->temp->dy;

	while (1)
	{
		mlx_pixel_put(window->mlx, window->mlx_win, data->temp->center_x, data->temp->center_y, data->settings->player_color);
		if (data->temp->center_x == data->temp->end_x && data->temp->center_y == data->temp->end_y)
			break ;
		e2 = 2 * data->temp->err;
		if (e2 >= data->temp->dy)
		{
			data->temp->err += data->temp->dy;
			data->temp->center_x += data->temp->sx;
		}
		if (e2 <= data->temp->dx)
		{
			data->temp->err += data->temp->dx;
			data->temp->center_y += data->temp->sy;
		}
	}
}

void	draw_player_direction(t_data *data, t_window *window)
{
	data->temp->angle_rad = (data->player->player_direction - 90) * M_PI / 180.0;
	data->temp->center_x = data->player->player_position[0][0];
	data->temp->center_y = data->player->player_position[0][1];
	calculate_end_point(data, data->settings->direction_line_length);
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

void	draw_tile(t_window *window, int tile_size, int tile_x, int tile_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			mlx_pixel_put(window->mlx, window->mlx_win, tile_x + i, tile_y + j, color);
			j++;
		}
		i++;
	}
}

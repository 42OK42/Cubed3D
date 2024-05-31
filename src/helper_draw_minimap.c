/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_drawlevel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:55:52 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 16:36:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/cubed3D.h"

void	calculate_end_point(t_data *data, int length)
{
	data->temp->end_x = data->temp->center_x + (int)(length * cos(data->temp->angle_rad));
	data->temp->end_y = data->temp->center_y + (int)(length * sin(data->temp->angle_rad));
}

void	bresenham_algorithm(t_data *data, t_mlx *mlx)
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
		mlx_pixel_put(mlx->mlx, mlx->mlx_win_minimap, data->temp->center_x, data->temp->center_y, data->settings->player_color);
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

void	draw_tile(t_mlx *mlx, int tile_size, int tile_x, int tile_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			mlx_pixel_put(mlx->mlx, mlx->mlx_win_minimap, tile_x + i, tile_y + j, color);
			j++;
		}
		i++;
	}
}

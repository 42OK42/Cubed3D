/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/22 18:42:58 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	event_hooks(t_data *data)
{
	if (data->settings->open_minimap)
	{
		mlx_hook(data->mlx->mlx_win_minimap, 2, 1L << 0, on_press, data);
		mlx_hook(data->mlx->mlx_win_minimap, 17, 0, close_window, data);
	}
	mlx_hook(data->mlx->mlx_win, 2, 1L << 0, on_press, data);
	mlx_hook(data->mlx->mlx_win, 17, 0, close_window, data);
	return (1);
}

int	game_loop(t_data *data)
{
	event_hooks(data);
	mlx_loop_hook(data->mlx->mlx, update_frame, data);
	mlx_loop(data->mlx->mlx);
	return (1);
}

int	update_frame(t_data *data)
{
	if (data->mlx->needs_redraw)
	{
		raycaster(data);
		draw_3d_view(data);
		if (data->settings->open_minimap)
		{
			draw_minimap(data, data->mlx);
			if (data->settings->show_rays)
				draw_rays(data, data->mlx);
		}
		mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, data->mlx->img_ptr, 0, 0);
		if (data->mlx->old_img_ptr)
			mlx_destroy_image(data->mlx->mlx, data->mlx->old_img_ptr);
		data->mlx->old_img_ptr = data->mlx->img_ptr;
		data->mlx->img_ptr = mlx_new_image(data->mlx->mlx, data->settings->window_width, data->settings->window_height);
		data->mlx->data_addr = mlx_get_data_addr(data->mlx->img_ptr, &data->mlx->bits_per_pixel, &data->mlx->size_line, &data->mlx->endian);
		data->mlx->needs_redraw = 0;
	}
	return (1);
}

int	on_press(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		close_window(data);
		return (0);
	}
	else if (keycode == 0 || keycode == 97 || keycode == 2 || keycode == 100 || keycode == 1 || keycode == 115 || keycode == 13 || keycode == 119)
	{
		if (keycode == 0 || keycode == 97)
			update_player_direction(data, 'l');
		else if (keycode == 2 || keycode == 100)
			update_player_direction(data, 'r');
		else if (keycode == 1 || keycode == 115)
			update_player_position(data, 'd');
		else if (keycode == 13 || keycode == 119)
			update_player_position(data, 'u');
		data->mlx->needs_redraw = 1;
		return (1);
	}
	return (0);
}

int	is_position_walkable(t_data *data, float x, float y)
{
	int		map_x;
	int		map_y;
	int		tile_size;
	float	buffer;

	tile_size = data->settings->tile_size;
	buffer = tile_size * 0.05;
	map_x = x / tile_size;
	map_y = y / tile_size;
	if (data->map[map_y][map_x] == '1')
		return (0);
	if (data->map[map_y][map_x] != '1')
	{
		if (x - (map_x * tile_size) < buffer && map_x > 0 && data->map[map_y][map_x - 1] == '1')
			return (0);
		if ((map_x + 1) * tile_size - x < buffer && map_x < data->map_width - 1 && data->map[map_y][map_x + 1] == '1')
			return (0);
		if (y - (map_y * tile_size) < buffer && map_y > 0 && data->map[map_y - 1][map_x] == '1')
			return (0);
		if ((map_y + 1) * tile_size - y < buffer && map_y < data->map_height - 1 && data->map[map_y + 1][map_x] == '1')
			return (0);
	}
	return (1);
}

void	update_player_position(t_data *data, char direction)
{
	int		move_step;
	double	angle_rad;
	float	new_x;
	float	new_y;

	move_step = data->settings->move_step;
	angle_rad = (data->player->player_direction - 90) * M_PI / 180.0;
	if (direction == 'u')
	{
		new_x = data->player->player_position[0][0] + (move_step * cos(angle_rad));
		new_y = data->player->player_position[0][1] + (move_step * sin(angle_rad));
	}
	else if (direction == 'd')
	{
		new_x = data->player->player_position[0][0] - (move_step * cos(angle_rad));
		new_y = data->player->player_position[0][1] - (move_step * sin(angle_rad));
	}
	else
		return ;
	if (is_position_walkable(data, new_x, new_y))
	{
		data->player->player_position[0][0] = new_x;
		data->player->player_position[0][1] = new_y;
	}
}

void	update_player_direction(t_data *data, char direction)
{
	int	rotate_step;

	rotate_step = data->settings->rotation_step;
	if (direction == 'l')
	{
		data->player->player_direction -= rotate_step;
		if (data->player->player_direction < 0)
			data->player->player_direction += 360;
	}
	else if (direction == 'r')
	{
		data->player->player_direction += rotate_step;
		if (data->player->player_direction >= 360)
			data->player->player_direction -= 360;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/17 18:57:19 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	event_hooks(t_data *data)
{
	if (data->settings->open_minimap)
	{
		mlx_hook(data->mlx->mlx_win_minimap, 17, 0, close_window, data);
		if (data->temp->exited != 1)
			mlx_hook(data->mlx->mlx_win_minimap, 2, 1L << 0, on_press, data);
	}
	mlx_hook(data->mlx->mlx_win, 17, 0, close_window, data);
	if (data->temp->exited != 1)
		mlx_hook(data->mlx->mlx_win, 2, 1L << 0, on_press, data);
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
		if (data->mlx->mlx_win_minimap != NULL && \
		data->settings->open_minimap && data->temp->exited != 1)
		{
			draw_minimap(data);
			if (data->settings->show_rays)
				draw_rays(data);
		}
		if (data->temp->exited != 1)
			mlx_put_image_to_window(data->mlx->mlx, data->mlx->mlx_win, \
				data->mlx->img_ptr, 0, 0);
		if (data->mlx->old_img_ptr)
			mlx_destroy_image(data->mlx->mlx, data->mlx->old_img_ptr);
		data->mlx->old_img_ptr = data->mlx->img_ptr;
		data->mlx->img_ptr = mlx_new_image(data->mlx->mlx, \
			data->settings->window_width, data->settings->window_height);
		data->mlx->data_addr = mlx_get_data_addr(data->mlx->img_ptr, \
			&data->mlx->bits_per_pixel, &data->mlx->size_line, \
			&data->mlx->endian);
		data->mlx->needs_redraw = 0;
	}
	return (1);
}

int	on_press(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		data->mlx->needs_redraw = 0;
		close_window(data);
		return (0);
	}
	else if ((keycode == 0 || keycode == 97 || keycode == 2 \
		|| keycode == 100 || keycode == 1 || keycode == 115 || \
		keycode == 13 || keycode == 119 || keycode == 65361 || \
		keycode == 65363 || keycode == 65362 || keycode == 65364 ||
		keycode == 113 || keycode == 101))
	{
		if (keycode == 113)
			update_player_direction(data, 'l');
		else if (keycode == 101)
			update_player_direction(data, 'r');
		if (keycode == 0 || keycode == 97 || keycode == 65361)
			update_player_position(data, 'l');
		else if (keycode == 2 || keycode == 100 || keycode == 65363)
			update_player_position(data, 'r');
		else if (keycode == 1 || keycode == 115 || keycode == 65364)
			update_player_position(data, 'd');
		else if (keycode == 13 || keycode == 119 || keycode == 65362)
			update_player_position(data, 'u');
		data->mlx->needs_redraw = 1;
		return (1);
	}
	return (0);
}

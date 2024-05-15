/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 19:21:40 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	event_hooks(t_data *data)
{
	//mlx_hook(data->window->mlx_win, 2, 1L << 0, on_press, data);
	mlx_hook(data->window->mlx_win, 17, 0, close_window, data);
	return (1);
}

int	game_loop(t_data *data)
{
	event_hooks(data);
	mlx_loop(data->window->mlx);
	return (1);
}

/* int	on_press(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		close_window(data);
		return (0);
	}
	else if (keycode == 0 || keycode == 97)
		update_player_position(data, 'l');
	else if (keycode == 2 || keycode == 100)
		update_player_position(data, 'r');
	else if (keycode == 1 || keycode == 115)
		update_player_position(data, 'd');
	else if (keycode == 13 || keycode == 119)
		update_player_position(data, 'u');
	return (0);
} */

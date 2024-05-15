/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:16:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 17:17:03 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	on_press(int keycode, t_data *data)
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
}

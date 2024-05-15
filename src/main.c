/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:28 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 18:54:23 by okrahl           ###   ########.fr       */
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

int	main(void)
{
	t_data	*data;

	data = initialize_data();
	print_map(data);
	data->window = initialize_window(data);
	game_loop(data);
	return (1);
}

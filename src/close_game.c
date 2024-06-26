/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:09 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 16:36:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	close_window(void *param)
{
	t_data	*data;

	data = param;
	mlx_clear_window(data->mlx->mlx, data->mlx->mlx_win_minimap);
	mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win_minimap);
	mlx_destroy_display(data->mlx->mlx);
	exit(0);
	return (0);
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void	free_data(t_data *data)
{
	free_map(data);
	free(data->filename);
	free(data->mlx->mlx);
	free(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:09 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/13 18:22:08 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	close_window(t_data *data)
{
	if (data->mlx->img_ptr != NULL)
	{
		mlx_destroy_image(data->mlx->mlx, data->mlx->img_ptr);
		data->mlx->img_ptr = NULL;
	}
	if (data->mlx->old_img_ptr != NULL)
	{
		mlx_destroy_image(data->mlx->mlx, data->mlx->old_img_ptr);
		data->mlx->old_img_ptr = NULL;
	}
	if (data->settings->open_minimap == 1 && data->mlx->mlx_win_minimap != NULL)
	{
		mlx_clear_window(data->mlx->mlx, data->mlx->mlx_win_minimap);
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win_minimap);
		data->mlx->mlx_win_minimap = NULL;
	}
	if (data->mlx->mlx_win != NULL)
	{
		mlx_clear_window(data->mlx->mlx, data->mlx->mlx_win);
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
		data->mlx->mlx_win = NULL;
	}
	free_data(data);
	exit(0);
}

void	free_rays(t_rays **rays, int num_rays)
{
	int	i;

	i = 0;
	while (i < num_rays)
	{
		free(rays[i]);
		i++;
	}
	free(rays);
}

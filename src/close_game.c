/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:09 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 20:35:22 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	close_window(t_data *data)
{
	if (data->mlx->img_ptr)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img_ptr);
	if (data->mlx->old_img_ptr)
		mlx_destroy_image(data->mlx->mlx, data->mlx->old_img_ptr);
	if (data->settings->open_minimap == 1)
	{
		mlx_clear_window(data->mlx->mlx, data->mlx->mlx_win_minimap);
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win_minimap);
	}
	mlx_clear_window(data->mlx->mlx, data->mlx->mlx_win);
	mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
	data->temp->exited = 1;
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
	//free(data->filename);
	free(data->player->player_position[0]);
	free(data->player->player_position);
	free(data->player);
	free(data->temp);
	free_rays(data->rays, data->settings->num_rays);
	free(data->settings);
	free_assets(data->assets);
	free_mlx(data);
	free(data);
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

void	free_assets(t_assets *assets)
{
	free_two_d_int_array(assets->wall_south);
	free_two_d_int_array(assets->wall_north);
	free_two_d_int_array(assets->wall_west);
	free_two_d_int_array(assets->wall_east);
	free(assets);
}

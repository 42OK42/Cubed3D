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
		data->mlx->mlx_win_minimap= NULL;
	}
	if (data->mlx->mlx_win != NULL)
	{
		mlx_clear_window(data->mlx->mlx, data->mlx->mlx_win);
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
		data->mlx->mlx_win = NULL;
	}
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
	if (data != NULL)
	{
		free_ray_loop(data);
		free_map(data);
		free(data->player->player_position[0]);
		free(data->player->player_position);
		free(data->player);
		free(data->temp);
		free_rays(data->rays, data->settings->num_rays);
		free(data->settings);
		free_assets(data->assets);
		free_mlx(data);
		free(data->file_content);
		free(data->color_row);
		free(data->file_info->path_no);
		free(data->file_info->path_ea);
		free(data->file_info->path_su);
		free(data->file_info->path_we);
		free(data->file_info->f_rgb);
		free(data->file_info->c_rgb);
		free(data->file_info);
		free(data->file_copy);
		free(data->map_pointer);
		// free(data->line_grid);	
		free(data);
		data = NULL;
	}
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
	free_two_d_int_array(assets->wall_sectfail);
	free_two_d_int_array(assets->wall_corner);
	free(assets);
}

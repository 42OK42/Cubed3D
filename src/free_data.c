/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:04:20 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/12 17:22:03 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map == NULL)
		return ;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void	free_mlx(t_data *data)
{
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
}

void	free_player(t_player *player)
{
	if (player != NULL)
	{
		if (player->player_position != NULL)
		{
			free(player->player_position[0]);
			free(player->player_position);
		}
		free(player);
	}
}

void	free_file_info(t_file_info *file_info)
{
	if (file_info != NULL)
	{
		if (file_info->path_no != NULL)
			free(file_info->path_no);
		if (file_info->path_ea != NULL)
			free(file_info->path_ea);
		if (file_info->path_su != NULL)
			free(file_info->path_su);
		if (file_info->path_we != NULL)
			free(file_info->path_we);
		if (file_info->f_rgb != NULL)
			free(file_info->f_rgb);
		if (file_info->c_rgb != NULL)
			free(file_info->c_rgb);
		free(file_info);
	}
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		free_rows(data);
		free_map(data);
		free_player(data->player);
		free_file_info(data->file_info);
		if (data->temp != NULL)
			free(data->temp);
		if (data->rays != NULL && data->settings != NULL)
			free_rays(data->rays, data->settings->num_rays);
		if (data->settings != NULL)
			free(data->settings);
		if (data->assets != NULL)
			free_assets(data->assets);
		if (data->mlx != NULL)
			free_mlx(data);
		if (data->color_row != NULL)
			free(data->color_row);
		if (data->file_copy != NULL)
			free(data->file_copy);
		if (data->file_content != NULL)
			free(data->file_content);
		free(data);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:28:44 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/30 16:14:11 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/cubed3D.h"

void	free_colors(char **colors, int index, t_data *data)
{
	if (index >= data->temp->num_colors)
		return ;
	free(colors[index]);
	free_colors(colors, index + 1, data);
}

void	free_pixels(char **pixels, int index, t_data *data)
{
	if (index >= data->temp->height)
		return ;
	free(pixels[index]);
	free_pixels(pixels, index + 1, data);
}

/* void	free_data_3d(t_data *data)
{
	int	i;

	if (data->mlx)
		free(data->mlx);
	if (data->settings)
		free(data->settings);
	if (data->player)
		free(data->player);
	if (data->temp)
		free(data->temp);
	if (data->rays)
	{
		i = 0;
		while (i < data->map_height)
		{
			free(data->rays[i]);
			i++;
		}
		free(data->rays);
	}
	if (data->assets)
		free(data->assets);
	if (data->filename)
		free(data->filename);
	if (data->map)
	{
		i = 0;
		while (i < data->map_height)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	free(data);
} */


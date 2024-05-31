/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:28:44 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/31 15:45:21 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/cubed3D.h"

void	free_two_d_array(char **pixel_map)
{
	int	i;

	i = 0;
	while (pixel_map[i])
	{
		free(pixel_map[i]);
		i++;
	}
	free(pixel_map);
}

void	free_three_d_array(char ***array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i][0])
			free(array[i][0]);
		if (array[i][1])
			free(array[i][1]);
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_image(char ***map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j])
				free(map[i][j]);
			j++;
		}
		free(map[i]);
		i++;
	}
	free(map);
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


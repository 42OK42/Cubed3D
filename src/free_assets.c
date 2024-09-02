/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:28:44 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 17:21:17 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

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

void	free_two_d_int_array(int **int_array)
{
	int	i;

	i = 0;
	while (int_array[i])
	{
		free(int_array[i]);
		i++;
	}
	free(int_array);
}

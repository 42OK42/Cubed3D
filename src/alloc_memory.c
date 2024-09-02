/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:16:00 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 19:38:40 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	**malloc_pixel_map(int height, int width)
{
	char	**map;
	int		i;
	int		k;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!map[i])
		{
			k = 0;
			while (k < i)
			{
				free(map[k]);
				k++;
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

char	***malloc_color_map(int height, int width)
{
	char	***map;
	int		i;
	int		j;

	map = (char ***)malloc(sizeof(char **) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (char **)malloc(sizeof(char *) * (width + 1));
		if (!map[i])
			return (free_three_d_array(map), NULL);
		j = 0;
		while (j < width)
		{
			map[i][j] = (char *)malloc(sizeof(char) * 9);
			j++;
		}
		i++;
	}
	return (map);
}

char	***malloc_color_entries(int num_colors)
{
	char	***colors;
	int		i;

	colors = (char ***)malloc(sizeof(char **) * num_colors);
	if (!colors)
		return (NULL);
	i = 0;
	while (i < num_colors)
	{
		colors[i] = (char **)malloc(sizeof(char *) * 2);
		if (!colors[i])
			return (free_three_d_array(colors), NULL);
		colors[i][0] = (char *)malloc(sizeof(char) * 2);
		colors[i][1] = (char *)malloc(sizeof(char) * 8);
		if (!colors[i][0] || !colors[i][1])
			return (free_three_d_array(colors), NULL);
		i++;
	}
	return (colors);
}

int	*initialize_color_row(t_data *data)
{
	int	*color_row;

	color_row = malloc(sizeof(int) * data->settings->window_height);
	if (!color_row)
		return (NULL);
	return (color_row);
}

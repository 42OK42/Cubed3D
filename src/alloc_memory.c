/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:16:00 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 15:51:12 by okrahl           ###   ########.fr       */
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

	map = (char ***)ft_calloc(sizeof(char **), (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (char **)ft_calloc(sizeof(char *), (width + 1));
		if (!map[i])
			return (free_three_d_array(map), NULL);
		j = 0;
		while (j < width)
		{
			map[i][j] = (char *)ft_calloc(sizeof(char), 9);
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

	colors = (char ***)ft_calloc(sizeof(char **), (num_colors + 1));
	if (!colors)
		return (NULL);
	i = 0;
	while (i < num_colors)
	{
		colors[i] = (char **)ft_calloc(sizeof(char *), (2 + 1));
		if (!colors[i])
			return (free_three_d_array(colors), NULL);
		colors[i][0] = (char *)ft_calloc(sizeof(char), (2 + 1));
		colors[i][1] = (char *)ft_calloc(sizeof(char), 9);
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

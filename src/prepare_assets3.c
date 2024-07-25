/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_assets3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:13:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 19:37:56 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	**get_pixel_map(char **xpm_lines, t_temp_assets *temp)
{
	char	**pixel_map;
	int		i;

	pixel_map = malloc_pixel_map(temp->height, temp->width);
	if (!pixel_map)
		return (NULL);
	i = 0;
	while (i < temp->height)
	{
		ft_strncpy(pixel_map[i], &xpm_lines[i \
			+ 5 + temp->num_colors][1], temp->width);
		pixel_map[i][temp->width] = '\0';
		i++;
	}
	pixel_map[i] = NULL;
	return (pixel_map);
}

char	***create_colored_map(char ***colors, \
	int num_colors, char **pixel_map, t_temp_assets *temp)
{
	char	***map;
	int		i;
	int		j;
	char	*color;

	map = malloc_color_map(temp->height, temp->width);
	i = 0;
	while (i < temp->height)
	{
		j = 0;
		while (j < temp->width)
		{
			color = find_color(colors, num_colors, pixel_map[i][j]);
			if (color)
			{
				ft_strncpy(map[i][j], color, 8);
				map[i][j][8] = '\0';
			}
			j++;
		}
		map[i][j] = NULL;
		i++;
	}
	map[i] = NULL;
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:45:51 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 15:45:54 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	**malloc_row_grid(char **line_grid)
{
	char	**row_grid;
	size_t	i;

	i = 0;
	row_grid = malloc(sizeof(char *) * (ft_strlen(line_grid[0]) + 1));
	while (i < ft_strlen(line_grid[0]))
	{
		row_grid[i] = malloc(sizeof(char) * (ft_arrlen(line_grid) + 1));
		i++;
	}
	return (row_grid);
}

void	ground_floor(t_data *data, char **file_content)
{
	if (**file_content == 'F')
	{
		data->file_info->f_rgb = extract_color(&(*file_content));
		data->file_info->fc = rgb_to_hex(data->file_info->f_rgb);
	}
	if (**file_content == 'C')
	{
		data->file_info->c_rgb = extract_color(&(*file_content));
		data->file_info->cc = rgb_to_hex(data->file_info->c_rgb);
	}
}

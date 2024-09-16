/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:45:51 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/12 18:30:44 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	**malloc_row_grid(char **line_grid)
{
	char	**row_grid;
	size_t	i;

	i = 0;
	row_grid = ft_calloc(sizeof(char *), (ft_strlen(line_grid[0]) + 1));
	while (i < ft_strlen(line_grid[0]))
	{
		row_grid[i] = ft_calloc(sizeof(char), (ft_arrlen(line_grid) + 1));
		i++;
	}
	return (row_grid);
}

void	ground_floor(t_data *data, char **file_content)
{
	if (**file_content == 'F')
	{
		data->file_info->f_rgb = extract_color(&(*file_content));
		data->file_info->fc = rgb_to_hex(data->file_info->f_rgb, data);
	}
	if (**file_content == 'C')
	{
		data->file_info->c_rgb = extract_color(&(*file_content));
		data->file_info->cc = rgb_to_hex(data->file_info->c_rgb, data);
	}
}

void	free_assets(t_assets *assets)
{
	if (assets->wall_south)
		free_two_d_int_array(assets->wall_south);
	if (assets->wall_north)
		free_two_d_int_array(assets->wall_north);
	if (assets->wall_west)
		free_two_d_int_array(assets->wall_west);
	if (assets->wall_east)
		free_two_d_int_array(assets->wall_east);
	free(assets);
}

int	check_empty_lines(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			i++;
			while (ft_isspace_without_newline(str[i]))
				i++;
			if (str[i] == '\n' && str[i +1] != '\n' && str[i +1] != '\0')
				error_exit("empty line in map", data);
		}
		else
			i++;
	}
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/02 16:36:06 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	parse_rgb_value(const char *str, int *index, t_data *data)
{
	int	value;

	value = 0;
	while (str[*index] != ',' && str[*index] != '\0')
	{
		if (str[*index] < '0' || str[*index] > '9')
		{
			error_exit("Wrong RGB value", data);
			return (-1);
		}
		value = value * 10 + (str[*index] - '0');
		(*index)++;
	}
	(*index)++;
	return (value);
}

int	rgb_to_hex(const char *rgb, t_data *data)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	hexcolor;

	if (rgb == NULL)
		error_exit("Not all RGB values provided", data);
	i = 0;
	r = parse_rgb_value(rgb, &i, data);
	if (r == -1)
		return (-1);
	g = parse_rgb_value(rgb, &i, data);
	if (g == -1)
		return (-1);
	b = parse_rgb_value(rgb, &i, data);
	if (b == -1)
		return (-1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("RGB-values must be between 0 and 255", data);
	hexcolor = (r << 16) | (g << 8) | b;
	return (hexcolor);
}

int	map_started(char *file_content)
{
	while (*file_content != '\n' && *file_content)
	{
		if (*file_content != '0' && *file_content != '1' \
			&& *file_content != 'N' && *file_content != 'S' \
			&& *file_content != 'E' && *file_content != 'W' && \
			*file_content != ' ')
			return (0);
		file_content++;
	}
	return (1);
}

int	line_is_map(char *file_content)
{
	while (*file_content != '\n' && *file_content != '\0' ) 
	{
		if (*file_content != '0' && *file_content != '1' \
			&& *file_content != 'N' && *file_content != 'S' \
			&& *file_content != 'E' && *file_content != 'W' && \
			*file_content != ' ')
			return (0);
		file_content++;
		if (*file_content == '\n' && *(file_content - 1) == '1')
		{
			return (1);
		}
	}
	return (0);
}

int	not_all_elements_provided(t_data *data)
{
	if (!data->file_info->path_no || !data->file_info->path_su \
		|| !data->file_info->path_we || !data->file_info->path_ea \
		|| data->file_info->fc == -1 || \
		data->file_info->cc == -1)
		return (1);
	return (0);
}

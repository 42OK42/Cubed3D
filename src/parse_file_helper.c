/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/08/29 17:41:38 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	parse_rgb_value(const char *str, int *index)
{
	int	value;

	value = 0;
	while (str[*index] != ',' && str[*index] != '\0')
	{
		if (str[*index] < '0' || str[*index] > '9')
		{
			perror_exit("Wrong RGB value");
			return (-1);
		}
		value = value * 10 + (str[*index] - '0');
		(*index)++;
	}
	(*index)++;
	return (value);
}

int	rgb_to_hex(const char *rgb)
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	hexcolor;

	if (rgb == NULL)
		perror_exit("Not all RGB values provided");
	i = 0;
	r = parse_rgb_value(rgb, &i);
	if (r == -1)
		return (-1);
	g = parse_rgb_value(rgb, &i);
	if (g == -1)
		return (-1);
	b = parse_rgb_value(rgb, &i);
	if (b == -1)
		return (-1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		perror_exit("RGB-values must be between 0 and 255");
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

int	not_all_elements_provided(t_data *data)
{
	if (!data->file_info->path_NO || !data->file_info->path_SU \
		|| !data->file_info->path_WE || !data->file_info->path_EA \
		|| data->file_info->fc == -1 || \
		data->file_info->cc == -1)
		return (1);
	return (0);
}

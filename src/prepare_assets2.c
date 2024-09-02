/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_assets2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:48:53 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 19:36:03 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	hex_to_decimal(const char *hex_str)
{
	int	decimal_value;
	int	digit;

	decimal_value = 0;
	if (*hex_str == ' ')
		hex_str++;
	if (*hex_str == '#')
		hex_str++;
	while (*hex_str != '\0')
	{
		digit = 0;
		if (*hex_str >= '0' && *hex_str <= '9')
			digit = *hex_str - '0';
		else if (*hex_str >= 'A' && *hex_str <= 'F')
			digit = *hex_str - 'A' + 10;
		else if (*hex_str >= 'a' && *hex_str <= 'f')
			digit = *hex_str - 'a' + 10;
		else
			break ;
		decimal_value = (decimal_value * 16) + digit;
		hex_str++;
	}
	return (decimal_value);
}

int	**convert_to_hex(char ***image_before, t_temp_assets *temp)
{
	int	i;
	int	j;
	int	**image_result;

	image_result = (int **)malloc(sizeof(int *) * (temp->height + 1));
	if (!image_result)
		return (NULL);
	i = 0;
	while (i < 10)
	{
		image_result[i] = (int *)malloc(sizeof(int) * (temp->width + 1));
		if (!image_result[i])
			return (NULL);
		j = 0;
		while (j < 10)
		{
			image_result[i][j] = hex_to_decimal(image_before[i][j]);
			j++;
		}
		image_result[i][j] = '\0';
		i++;
	}
	image_result[i] = NULL;
	free_three_d_array(image_before);
	return (image_result);
}

char	*find_color(char ***colors, int num_colors, char pixel)
{
	int	i;

	i = 0;
	while (i < num_colors)
	{
		if (colors[i][0][0] == pixel)
		{
			return (colors[i][1]);
		}
		i++;
	}
	return (NULL);
}

char	***get_colors(char **xpm_lines, int num_colors)
{
	char	***colors;
	int		i;

	colors = malloc_color_entries(num_colors);
	if (!colors)
		return (NULL);
	i = 0;
	while (i < num_colors)
	{
		colors[i][0][0] = xpm_lines[i + 4][1];
		colors[i][0][1] = '\0';
		ft_strncpy(colors[i][1], &xpm_lines[i + 4][5], 8);
		i++;
	}
	return (colors);
}

t_temp_assets	*parse_header(char **xpm_lines)
{
	t_temp_assets	*temp;

	temp = (t_temp_assets *)malloc(sizeof(t_temp_assets));
	temp->num_colors = ft_atoi(&xpm_lines[3][7]);
	temp->chars_per_pixel = ft_atoi(&xpm_lines[3][9]);
	temp->width = (ft_atoi(&xpm_lines[3][1]));
	temp->height = (ft_atoi(&xpm_lines[3][4]));
	return (temp);
}

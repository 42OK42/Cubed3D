/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:27:33 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 15:29:28 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	find_map_width(t_data *data)
{
	int	max_length;
	int	current_length;
	int	i;

	i = 0;
	max_length = 0;
	while (data->map[i] != NULL)
	{
		current_length = ft_strlen(data->map[i]);
		if (current_length > max_length)
			max_length = current_length;
		i++;
	}
	max_length--;
	return (max_length);
}

int	find_map_height_before_map(t_data *data)
{
	int	map_height;
	int	i;

	i = 0;
	map_height = 0;
	while (data->map[i] != NULL)
	{
		map_height++;
		i++;
	}
	return (map_height);
}

int	get_image_height(int **right_image)
{
	int	i;

	i = 0;
	while (right_image[i])
		i++;
	return (i);
}

int	get_image_width(int **right_image)
{
	int	i;

	i = 0;
	while (right_image[0][i])
		i++;
	return (i);
}

int	ft_atoi_base(char *str, int base)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * base + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			res = res * base + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			res = res * base + str[i] - 'a' + 10;
		i++;
	}
	return (res * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:03:41 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 18:08:02 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	same_but_reverse(char **strarr, int len, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = len;
	while (strarr[i] != NULL )
	{
		j = len;
		while (strarr[i][j] != '\0')
		{
			while (strarr[i][j] == ' ' && strarr[i][j] == '\t')
				j--;
			if (strarr[i][j] != '1')
			{
				return (0);
				error_exit("map not enclosed properly", data);
			}
		}
		i++;
	}
	return (1);
}

int	starts_and_ends_with_wall(char **strarr, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strarr[i] != NULL )
	{
		j = 0;
		while (strarr[i][j] != '\0')
		{
			while (strarr[i][j] == ' ' && strarr[i][j] == '\t')
			{
				j++;
			}
			if (strarr[i][j] != '1')
			{
				return (0);
				error_exit("map not enclosed properly", data);
			}
			j++;
		}
		i++;
	}
	return (same_but_reverse(strarr, ft_strlen(strarr[0]), data));
}

long double	distance(t_point *start, t_point *end)
{
	if (start == NULL || end == NULL)
		return (1000);
	return (sqrt(pow(end->x - start->x, 2) + pow(end->y - start->y, 2)));
}

int	closest_multiple_of_tile(double num, int tile_size)
{
	int	remainder;

	remainder = fmod(num, (double)tile_size);
	if (remainder < tile_size / 2)
		return (num - remainder);
	else
		return (num + tile_size - remainder);
}

long double	absolute_difference(long double num1, long double num2)
{
	long double	diff;

	diff = num1 - num2;
	if (diff < 0)
		diff = -diff;
	return (diff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:45:51 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 15:45:54 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	invalid_space(char **strarr, int i, int j)
{
	if ((strarr[i][j + 1] != '0' && strarr[i][j + 1] != \
		'1' && strarr[i][j + 1] != 'N' && strarr[i][j + 1] != \
		'S' && strarr[i][j + 1] != 'E' && strarr[i][j + 1] != 'W') \
		|| (strarr[i][j - 1] != '0' && strarr[i][j - 1] != '1' && \
		strarr[i][j - 1] != 'N' && strarr[i][j - 1] != 'S' && \
		strarr[i][j - 1] != 'E' && strarr[i][j - 1] != 'W'))
		return (1);
	return (0);
}

int	no_grey_before_or_after_player(char **strarr)
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
			if (strarr[i][j] == 'N' || strarr[i][j] == 'S' \
			|| strarr[i][j] == 'E' || strarr[i][j] == 'W')
			{
				if (invalid_space(strarr, i, j))
					error_exit("player next to invalid space");
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check__invalid_chars(char **strarr)
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
			if ((strarr[i][j] != '0' && strarr[i][j] != \
				'1' && strarr[i][j] != 'N' && strarr[i][j] != \
				'S' && strarr[i][j] != 'E' && strarr[i][j] != 'W') \
				&& strarr[i][j] != ' ')
				error_exit("invalid chars in map");
			j++;
		}
		i++;
	}
	return (1);
}

int	check_chars(char **strarr)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (strarr[i] != NULL )
	{
		j = 0;
		while (strarr[i][j] != '\0')
		{
			if (strarr[i][j] == 'N' || strarr[i][j] == 'S' \
			|| strarr[i][j] == 'E' || strarr[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count < 1)
		error_exit("Player not defined correctly");
	if (count > 1)
		error_exit("multiple players defined");
	return (1);
}

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

int	same_but_reverse(char **strarr, int len)
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
			while (strarr[i][j] == ' ')
				j--;
			if (strarr[i][j] != '1')
			{
				return (0);
				error_exit("map not enclosed properly");
			}
		}
		i++;
	}
	return (1);
}

int	starts_and_ends_with_wall(char **strarr)
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
			while (strarr[i][j] == ' ')
			{
				j++;
			}
			if (strarr[i][j] != '1')
			{
				return (0);
				error_exit("map not enclosed properly");
			}
			j++;
		}
		i++;
	}
	return (same_but_reverse(strarr, ft_strlen(strarr[0])));
}

int	no_grey_before_or_after_white(char **strarr)
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
			if (strarr[i][j] == '0')
			{
				if ((strarr[i][j + 1] != '0' && strarr[i][j + 1] != \
					'1' && strarr[i][j + 1] != 'N' && strarr[i][j + 1] != \
					'S' && strarr[i][j + 1] != 'E' && strarr[i][j + 1] != 'W') \
					|| (strarr[i][j - 1] != '0' && strarr[i][j - 1] != '1' && \
					strarr[i][j - 1] != 'N' && strarr[i][j - 1] != 'S' && \
					strarr[i][j - 1] != 'E' && strarr[i][j - 1] != 'W'))
					error_exit("walkable mapspace not properly enclosed");
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_arrlen(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != NULL)
		i++;
	return (i);
}

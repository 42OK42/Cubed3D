/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:03:24 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 18:03:29 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	perror_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	error_exit(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	print_string_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i] != NULL)
	{
		ft_printf("\nstrArr[%d] #%s#", i, str_array[i]);
		i++;
	}
	ft_printf("\n");
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

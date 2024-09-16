/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:45:35 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/12 18:05:59 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	valid_map_chars(char *str)
{
	int		count;
	char	*p;

	count = 0;
	p = str;
	while (*p != '\0')
	{
		if (*p == 'N')
			count++;
		else if (*p == 'S')
			count++;
		else if (*p == 'E')
			count++;
		else if (*p == 'W')
			count++;
		else if (*p != '1' && *p != '0' && *p != ' ' \
				&& *p != '\t' && *p != '\n')
			return (0);
		p++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

int	only_valid_map_chars(char *str)
{
	char	*p;

	p = str;
	while (*p != '\0')
	{
		if (*p != '1' && *p != '0' && *p != ' ' \
			&& *p != '\t' && *p != '\n' \
			&& *p != 'N' && *p != 'S' \
			&& *p != 'E' && *p != 'W')
			return (0);
		p++;
	}
	return (1);
}

int	find_max_width(char **line_grid)
{
	int	max_length;
	int	current_length;
	int	i;

	max_length = 0;
	i = 0;
	while (line_grid != NULL)
	{
		current_length = ft_strlen(line_grid[i]);
		if (current_length > max_length)
			max_length = current_length;
		i++;
	}
	max_length--;
	return (max_length);
}

void	bunch(char **line_grid, char *new_line, int i)
{
	char	*phold;

	phold = line_grid[i];
	line_grid[i] = new_line;
	free(phold);
}

int	pad(char **line_grid, int max_width)
{
	int		i;
	int		len;
	char	*new_line;
	int		j;

	i = 0;
	while (line_grid[i] != NULL)
	{
		len = ft_strlen(line_grid[i]);
		if (len < max_width)
		{
			new_line = (char *)malloc((max_width + 1) * sizeof(char));
			if (new_line == NULL)
				return (-1);
			ft_strcpy(new_line, line_grid[i]);
			j = len;
			while (j < max_width)
				new_line[j++] = ' ';
			new_line[max_width] = '\0';
			bunch(line_grid, new_line, i);
		}
		i++;
	}
	return (0);
}

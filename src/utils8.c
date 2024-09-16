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

void	free_rows(t_data *data)
{
	int	i;

	i = 0;
	if (data->row_grid == NULL)
		return ;
	while (data->row_grid[i])
	{
		free(data->row_grid[i]);
		i++;
	}
	free(data->row_grid);
}

void	check_if_empty(char *file_content, t_data *data)
{
	while (*file_content != '\0' ) 
	{
		if (*file_content == '\n')
			return ;
		else
			file_content++;
	}
	error_exit("file empty or single line", data);
}

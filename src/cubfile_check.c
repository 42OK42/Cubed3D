/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:46:07 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/12 18:35:30 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	**lines_to_rows(char **line_grid)
{
	char	**row_grid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	row_grid = malloc_row_grid(line_grid);
	while (line_grid[0][i] != '\0')
	{
		j = 0;
		while (line_grid[j] != NULL)
		{
			row_grid[i][j] = line_grid[j][i];
			j++;
		}
		row_grid[i][j] = '\0';
		i++;
	}
	row_grid[i] = NULL;
	return (row_grid);
}

int	enclosed_by_walls(char **line_grid, char **row_grid, t_data *data)
{
	starts_and_ends_with_wall(line_grid, data);
	starts_and_ends_with_wall(row_grid, data);
	no_grey_before_or_after_white(line_grid, data);
	no_grey_before_or_after_white(row_grid, data);
	no_grey_before_or_after_player(line_grid, data);
	no_grey_before_or_after_player(row_grid, data);
	return (1);
}

int	check_surrounded_by_walls(char	**line_grid, t_data *data)
{
	data->row_grid = lines_to_rows(line_grid);
	enclosed_by_walls(line_grid, data->row_grid, data);
	return (0);
}

int	create_map(char *file_content, t_data *data)
{
	data->line_grid = ft_split(file_content, '\n');
	pad(data->line_grid, 57);
	data->map = data->line_grid;
	check_empty_lines(file_content, data);
	check__invalid_chars(data->line_grid, data);
	check_chars(data->line_grid, data);
	check_surrounded_by_walls(data->line_grid, data);
	return (0);
}

void	cubfile_check(char *mapfile, t_data *data)
{
	int		map_fd;
	int		bytes_read;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
		error_exit("Error opening file", data);
	data->file_content = ft_calloc(14400, 1);
	bytes_read = read(map_fd, data->file_content, 14400);
	if (bytes_read == -1) 
	{
		free(data->file_content);
		close(map_fd);
		error_exit("Error reading file", data);
	}
	data->file_content[bytes_read] = '\0';
	data->map_pointer = read_fileinfo(data->file_content, data);
	create_map(data->map_pointer, data);
}

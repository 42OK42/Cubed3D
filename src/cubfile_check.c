/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:46:07 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 15:46:10 by dgacic           ###   ########.fr       */
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

int	enclosed_by_walls(char **line_grid, char **row_grid)
{
	starts_and_ends_with_wall(line_grid);
	starts_and_ends_with_wall(row_grid);
	no_grey_before_or_after_white(line_grid);
	no_grey_before_or_after_white(row_grid);
	return (1);
}

int	check_surrounded_by_walls(char	**line_grid)
{
	char	**row_grid;
	int		i;

	i = 0;
	row_grid = lines_to_rows(line_grid);
	enclosed_by_walls(line_grid, row_grid);
	while (i < (int)ft_strlen(line_grid[0]))
	{
		free(row_grid[i]);
		i++;
	}
	free(row_grid);
	return (0);
}

int	create_map(char *file_content, t_data *data)
{
	data->line_grid = ft_split(file_content, '\n');
	pad(data->line_grid, 57);
	check_surrounded_by_walls(data->line_grid);
	data->map = data->line_grid;
	return (0);
}

void	cubfile_check(char *mapfile, t_data *data)
{
	int		map_fd;
	int		bytes_read;

	map_fd = open(mapfile, O_RDONLY);
	if (map_fd == -1)
		perror_exit("Error opening file");
	data->file_content = malloc(14400);
	bytes_read = read(map_fd, data->file_content, 14400);
	if (bytes_read == -1) 
	{
		free(data->file_content);
		close(map_fd);
		perror_exit("Error reading file");
	}
	data->file_content[bytes_read] = '\0';
	data->map_pointer = read_fileinfo(data->file_content, data);
	create_map(data->map_pointer, data);
}

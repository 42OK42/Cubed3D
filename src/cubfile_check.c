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
			strcpy(new_line, line_grid[i]);
			j = len;
			while (j < max_width)
				new_line[j++] = ' ';
			new_line[max_width] = '\0';
			line_grid[i] = new_line;
		}
		i++;
	}
	return (0);
}

char	**malloc_row_grid(char **line_grid)
{
	char	**row_grid;
	size_t	i;

	i = 0;
	row_grid = malloc(sizeof(char *) * (ft_strlen(line_grid[0]) + 1));
	while (i < ft_strlen(line_grid[0]))
	{
		row_grid[i] = malloc(sizeof(char) * (ft_arrlen(line_grid) + 1));
		i++;
	}
	return (row_grid);
}

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
	return(1);
}

int	check_surrounded_by_walls(char	**line_grid)
{
	char **row_grid;

	row_grid = lines_to_rows(line_grid);
	enclosed_by_walls(line_grid, row_grid);
	return (0);
}

int create_map(char *file_content, t_data *data)
{
	char	**line_grid;

	line_grid = ft_split(file_content,'\n');
	pad(line_grid, 57);
	check_surrounded_by_walls(line_grid);
	// print_string_array(line_grid);
	data->map = line_grid;
	return (0);
}

void	cubfile_check(char *mapfile, t_data *data)
{
	int		map_fd;
	char	*file_content;
	int		bytesRead;
	// int		max_width;

	map_fd = open(mapfile, O_RDONLY); // Try to open the file for reading
	if (map_fd == -1)
		perror_exit("Error opening file");
	file_content = malloc(14400);
	bytesRead = read(map_fd, file_content, 14400);
	if (bytesRead == -1) 
	{
		free(file_content);
		close(map_fd);
		perror_exit("Error reading file");
	}
	file_content[bytesRead] = '\0'; // Null-terminate the file_content
	file_content = read_fileinfo(file_content, data); // file_content now equal to the map content
	// printf(" file content :\n%s", file_content);
	create_map(file_content, data);
}

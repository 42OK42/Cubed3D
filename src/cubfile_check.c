#include "../incl/cubed3D.h"

int valid_map_chars(char *str)
{
	int count;
	char *p;

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
		else if (*p != '1' && *p != '0' && *p != ' ' && *p != '\t' && *p != '\n')
			return (0);
		p++;
	}
	if (count == 1)
		return (1);
	else
		return (0);
}

int only_valid_map_chars(char *str)
{
	char *p;

	p = str;
	while (*p != '\0')
	{
	if (*p != '1' && *p != '0' && *p != ' ' && *p != '\t' && *p != '\n' \
	 && *p != 'N' && *p != 'S' && *p != 'E' && *p != 'W')
			return (0);
		p++;
	}
	return (1);
}

// int	all_textures_provided(char *filecontent)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	while (i != '\n')
// 	{

// 	}


// }

// char	*read_til_map(char *file_content)
// {

// }

// char	*iterate_pointer(char *file_content)
// {

// }

// char	*iterate_pointer(char *file_content)
// {
// 	char	*copy;
// 	char	*line;
// 	int		i;

// 	copy = ft_strdup(file_content);
// 	line = strtok(copy,"\n");
// 	while (!only_valid_map_chars(line))
// 	{
// 		line = strtok(NULL,"\n");
// 	}
// 	while(line[i] != '\0')
// 		i++;
// 	line[i] = '\n';
// 	return(line);
// }

// int	map_check(char *file_content, t_data *data)
// {
// 	// char	*texture_content;

// 	// texture_content = read_til_map(file_content);
// 	printf("file_content:\n %s",file_content);
// 	line_gridntent = iterate_pointer(file_content);
// 	printf("test2");
// 	printf("\nmap_content:\n %s",line_gridntent);
// 	// if(!all_textures_provided(texture_content))
// 	// 	perror_exit("textures error");
// 	// if(!lines_and_rows_closed(map_content))
// 	// 	perror_exit("map not closed");
// 	if(!valid_map_chars(line_gridntent))
// 		error_exit("invalid chars in map");
// 	return (0);
// }


int	find_max_width(char **line_grid)
{
    int max_length = 0;
    int current_length;
    int i = 0;

    // Iterate through each line using a while loop
    while (line_grid != NULL)
	{
        current_length = ft_strlen(line_grid[i]);
        if (current_length > max_length)
            max_length = current_length;
        i++; // Move to the next line
    }
	max_length--;
    return (max_length);
}

int pad(char **line_grid, int max_width)
{
    int i = 0;

    while (line_grid[i] != NULL)
	{
        int len = ft_strlen(line_grid[i]);
        if (len < max_width) {
            char *new_line = (char *)malloc((max_width + 1) * sizeof(char));
            if (new_line == NULL)
                return -1;
            strcpy(new_line, line_grid[i]);
            int j = len;
            while (j < max_width)
                new_line[j++] = ' ';
            new_line[max_width] = '\0';
            line_grid[i] = new_line;
        }
        i++;
    }
    return 0;
}

char	**malloc_row_grid(char **line_grid)
{
	char	**row_grid;
	size_t	i;

	i = 0;
	row_grid = malloc(sizeof(char *) * (ft_strlen(line_grid[0]) + 1));
	while (i < ft_strlen(line_grid[0]))
	{
		row_grid[i] = malloc(sizeof(char) * (ft_arrlen(line_grid)+1));
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
	// starts_and_ends_with_wall(line_grid);
	// starts_and_ends_with_wall(row_grid);
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
	//max_width = find_max_width(line_grid);
	// ft_printf("line_grid\n");
	print_string_array(line_grid);
	data->map = line_grid;
	return (0);
}

t_file_info	*initialize_file_info()
{
	t_file_info	*file_info;

	file_info = malloc(sizeof(t_file_info));
	if (!file_info)
		return (NULL);
	file_info->ceiling_color = NULL;
	file_info->floor_color = NULL;
	file_info->path_NO = NULL;
	file_info->path_SU = NULL;
	file_info->path_WE = NULL;
	file_info->path_EA = NULL;
	return (file_info);
}

char	*skip_empty_lines(char *file_content)
{
	while (*file_content == '\n' || *file_content == ' ' || *file_content == '\t')
		file_content++;
	return (file_content);
}

int	is_element(char *file_content)
{
	if (*file_content == 'N' || *file_content == 'S' || *file_content == 'W' || *file_content == 'E' || *file_content == 'F' || *file_content == 'C')
		return (1);
	return (0);
}

size_t	find_length(char *start, char *end)
{
	size_t		length;

	length = 0;
	while (start != end)
	{
		if (*start == '\n')
			break;
		while (ft_isspace(*start))
			start++;
		if (*start == '\n')
			break;
		start++;
		length++;
	}
	return (length);
}

char	*copy_without_spaces(char *start, char *end)
{
	char	*path;
	size_t	path_length;
	char	*path_start;

	path_length = find_length(start, end);
	path = malloc(path_length + 1);
	if (!path)
		return (NULL);
	path_start = path;
	while (start != end)
	{
		while (ft_isspace(*start))
			start++;
		*path = *start;
		if (*start == '\n')
			break;
		start++;
		path++;
	}
	*path = '\0';
	return (path_start);
}

char	*copy_path(char *start, char *end)
{
	char	*path;
	char	*path_start;

	path = malloc((end - start) + 1);
	if (!path)
		return (NULL);
	path_start = path;
	while (start != end)
	{
		*path = *start;
		start++;
		path++;
	}
	*path = '\0';
	return (path_start);
}

char *extract_path(char *file_content)
{
	char	*path_start;
	char	*path_end;
	char	*path;

	while (*file_content != 'O' && *file_content != 'E' && *file_content != 'A') 
		file_content++;
	file_content++;
	while (ft_isspace(*file_content))
		file_content++;
	path_start = file_content;
	while (*file_content != '\n')
		file_content++;
	path_end = file_content;
	path = NULL;
	path = copy_path(path_start, path_end);
	return (path);
}

char	*extract_color(char *file_content)
{
	char	*path_start;
	char	*path_end;
	char	*path;

	file_content++;
	path_start = file_content;
	while (*file_content != '\n')
		file_content++;
	path_end = file_content;
	path = NULL;
	path = copy_without_spaces(path_start, path_end);
	return (path);
}

void	extract_element(t_data *data, char *file_content)
{
	if (*file_content == 'N')
		data->file_info->path_NO = extract_path(++file_content);
	if (*file_content == 'S')
		data->file_info->path_SU = extract_path(++file_content);
	if (*file_content == 'W')
		data->file_info->path_WE = extract_path(++file_content);
	if (*file_content == 'E')
		data->file_info->path_EA = extract_path(++file_content);
	if (*file_content == 'F')
		data->file_info->floor_color = extract_color(file_content);
	if (*file_content == 'C')
		data->file_info->ceiling_color = extract_color(file_content);
}

int map_started(char *file_content)
{
	if (file_content)
	{
		if (*file_content == '1' || *file_content == '0')
		{
			while (ft_isspace(*file_content) || *file_content == 'N' || *file_content == 'S' || *file_content == 'W' || *file_content == 'E')
				file_content--;
			if (*file_content == '\n')
				return (1);
		}
	}
	return (0);
}

char	*read_fileinfo(char *file_content, t_data *data)
{
	int		elements_found;

	elements_found = 0;
	data->file_info = initialize_file_info();
	while (map_started(file_content) == 0 && file_content)
	{
		file_content = skip_empty_lines(file_content);
		if (is_element(file_content))
		{
			extract_element(data, file_content);
			elements_found++;
			file_content++;
		}
		file_content++;
	}
	return (file_content);
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
	while (*file_content != '\n' && *file_content)
		file_content++;
	printf("data->file_info->path_NO: %s\n", data->file_info->path_NO);
	printf("data->file_info->path_SU: %s\n", data->file_info->path_SU);
	printf("data->file_info->path_WE: %s\n", data->file_info->path_WE);
	printf("data->file_info->path_EA: %s\n", data->file_info->path_EA);
	printf("data->file_info->floor_color: %s\n", data->file_info->floor_color);
	printf("data->file_info->ceiling_color: %s\n", data->file_info->ceiling_color);
	// map_check(file_content, data);
	create_map(file_content, data);
}
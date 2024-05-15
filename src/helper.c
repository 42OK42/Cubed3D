#include "../incl/cubed3D.h"

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
	printf("\n");
}

int	find_map_height(t_data *data)
{
	int	i;
	int	j;

	j = data->map_width;
	i = 0;
	while (data->map[i][j + 1])
		i++;
	return (i);
}

int	find_map_width(t_data *data)
{
	int	i;

	i = 0;
	if (!data->map)
		return (0);
	while (data->map[0][i] != '\n' && data->map[0][i] != '\0')
		i++;
	return (i - 1);
}

int	find_map_height_before_map(t_data *data)
{
	int		fd;
	int		map_height;
	char	*map_line;

	fd = open(data->filename, O_RDONLY);
	if (fd == -1)
		return (0);
	map_height = 1;
	map_line = get_next_line(fd);
	if (!map_line)
		return (0);
	while (map_line)
	{
		if (strchr(map_line, '\n') != NULL)
			map_height++;
		free(map_line);
		map_line = get_next_line(fd);
	}
	free(map_line);
	close(fd);
	return (map_height);
}

t_data	*initialize_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->filename = "map.cub";
	data->map_height = find_map_height_before_map(data);
	data->map = map_read(data);
	data->map_width = find_map_width(data);
	data->map_height = find_map_height(data);
	return (data);
}

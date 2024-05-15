#include "../incl/cubed3D.h"

char	**map_read(t_data *data)
{
	int		fd;
	char	*map_line;
	int		i;
	char	**map_array;

	fd = open(data->filename, O_RDONLY);
	if (fd == -1)
		return (printf("Error:\n File not found\n"), NULL);
	i = 0;
	if (data->map_height < 1)
		return (printf("Error:\n No Map!\n"), NULL);
	map_array = (char **)malloc((data->map_height + 1) * sizeof(char *));
	if (!map_array)
		return (0);
	while (i <= data->map_height)
	{
		map_line = get_next_line(fd);
		if (!map_line)
			break ;
		map_array[i] = ft_strdup(map_line);
		free(map_line);
		i++;
	}
	map_array[i] = NULL;
	return (close(fd), map_array);
}

void	*open_window(void	*mlx, t_data *data)
{
	int		i;
	void	*mlx_win;

	i = 0;
	while (data->map[0][i] != '\n' && data->map[0][i] != '\0')
		i++;
	mlx_win = mlx_new_window(mlx, (i * 100), \
	((data->map_height + 1) * 100), "Hello world!");
	return (mlx_win);
}

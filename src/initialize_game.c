#include "../incl/cubed3D.h"

t_window	*initialize_window(t_data *data)
{
	t_window	*window;

	window = (t_window *) malloc (sizeof(t_window));
	window->mlx = NULL;
	window->mlx = mlx_init();
	window->mlx_win = mlx_new_window(window->mlx, (data->map_width * 100), ((data->map_height + 1) * 100), "Hello world!");
	printf("Window created\n");
	printf("window->mlx_win: %p\n", window->mlx_win);
	//draw_map(data);
	return (window);
}
/* 
void	draw_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_wall(data, i, j);
			else if (data->map[i][j] == '0')
				draw_floor(data, i, j);
			else if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || \
			data->map[i][j] == 'E' || data->map[i][j] == 'W')
				draw_player(data, i, j);
			j++;
		}
		i++;
	}
} */

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

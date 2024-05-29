#include "../incl/cubed3D.h"

t_mlx	*initialize_mlx(t_data *data)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) malloc (sizeof(t_mlx));
	mlx->needs_redraw = 0;
	mlx->mlx = NULL;
	mlx->mlx = mlx_init();
	if (data->settings->open_minimap)
	{
		mlx->mlx_win_minimap = mlx_new_window(mlx->mlx, (data->map_width * data->settings->tile_size), ((data->map_height) * data->settings->tile_size), "Minimap");
		draw_minimap(data, mlx);
	}
	mlx->mlx_win = mlx_new_window(mlx->mlx, data->settings->window_width, data->settings->window_height, "Cub3D");
	//printf("Window created\n");
	//printf("mlx->mlx_win_minimap: %p\n", mlx->mlx_win_minimap);
	return (mlx);
}

char	**map_read(t_data *data)
{
	int		fd;
	char	*map_line;
	int		i;
	char	**map_array;

	fd = open(data->filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error:\n File not found\n"), NULL);
	i = 0;
	if (data->map_height < 1)
		return (ft_printf("Error:\n No Map!\n"), NULL);
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

// char	**map_read(t_data *data)
// {
// 	int		fd;
// 	char	*map_str;
// 	char	**map_array;
// 	int		bytesRead;

// 	fd = open(data->filename, O_RDONLY);
// 	if (fd == -1)
// 		return (ft_printf("Error:\n File not found\n"), NULL);
// 	if (data->map_height < 1)
// 		return (ft_printf("Error:\n No Map!\n"), NULL);
// 	map_array = (char **)malloc((data->map_height + 1) * sizeof(char *));
// 	if (!map_array)
// 		return (0);
// 	map_str = NULL;
// 	bytesRead = 0;
// 	bytesRead = read(fd, map_str, bytesRead);
// 	write(2, map_str, ft_strlen(map_str));

// 	// while (i <= data->map_height)
// 	// {
// 	// 	map_line = get_next_line(fd);
// 	// 	if (!map_line)
// 	// 		break ;
// 	// 	map_array[i] = ft_strdup(map_line);
// 	// 	free(map_line);
// 	// 	i++;
// 	// }
// 	// map_array[i] = NULL;
// 	return (close(fd), map_array);
// }
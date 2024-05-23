#include "../incl/cubed3D.h"

t_window	*initialize_window(t_data *data)
{
	t_window	*window;

	window = (t_window *) malloc (sizeof(t_window));
	window->mlx = NULL;
	window->mlx = mlx_init();
	window->mlx_win = mlx_new_window(window->mlx, (data->map_width * data->settings->tile_size), ((data->map_height) * data->settings->tile_size), "Hello world!");
	printf("Window created\n");
	//printf("window->mlx_win: %p\n", window->mlx_win);
	draw_element(data, window, '1', data->settings->wall_color);
	draw_element(data, window, '0', data->settings->background_color);
	draw_element(data, window, 'N', data->settings->background_color);
	draw_player(data, window);
	return (window);
}

void	draw_player(t_data *data, t_window *window)
{
	int	px;
	int	py;
	int	offset;
	int	i;
	int	j;

	px = data->player_position[0][0];
	py = data->player_position[0][1];
	offset = 5;
	i = px - offset;
	while (i <= px + offset)
	{
		j = py - offset;
		while (j <= py + offset)
		{
			mlx_pixel_put(window->mlx, window->mlx_win, i, j, data->settings->player_color);
			j++;
		}
		i++;
	}
}

void	draw_element(t_data *data, t_window *window, char c, int c_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == c)
				draw_tile(window, data->settings->tile_size, x * data->settings->tile_size, y * data->settings->tile_size, c_color);
			x++;
		}
		y++;
	}
}

void	draw_tile(t_window *window, int tile_size, int tile_x, int tile_y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < tile_size)
	{
		j = 0;
		while (j < tile_size)
		{
			mlx_pixel_put(window->mlx, window->mlx_win, tile_x + i, tile_y + j, color);
			j++;
		}
		i++;
	}
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:42:03 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 17:42:47 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

t_mlx	*initialize_mlx(t_data *data)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->needs_redraw = 1;
	mlx->mlx = NULL;
	mlx->mlx = mlx_init();
	if (data->settings->open_minimap)
		mlx->mlx_win_minimap = mlx_new_window(mlx->mlx, \
			(data->map_width * data->settings->tile_size), ((data->map_height) \
			* data->settings->tile_size), "Minimap");
	mlx->mlx_win = mlx_new_window(mlx->mlx, \
		data->settings->window_width, data->settings->window_height, "Cubed3D");
	mlx->img_ptr = mlx_new_image(mlx->mlx, \
		data->settings->window_width, data->settings->window_height);
	mlx->data_addr = mlx_get_data_addr(mlx->img_ptr, \
		&mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	mlx->old_img_ptr = NULL;
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

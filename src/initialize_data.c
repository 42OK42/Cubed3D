/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:19 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/23 13:06:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	find_map_width(t_data *data)
{
	int	i;

	i = 0;
	if (!data->map)
		return (0);
	while (data->map[0][i] != '\n' && data->map[0][i] != '\0')
		i++;
	return (i);
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

t_settings	*initialize_settings(t_data *data)
{
	t_settings	*settings;

	data++;
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	settings->background_color = 0xFFFFFF;
	settings->wall_color = 0x467836;
	settings->player_color = 0x0000FF;
	settings->tile_size = 100;
	return (settings);
}

t_player	*initialize_player(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->player_position = initialize_player_position(data);
	player->player_direction = initialize_player_direction(data, player->player_position);
	printf("player_direction: %d\n", player->player_direction);
	return (player);
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
	data->settings = initialize_settings(data);
	data->player = initialize_player(data);
	data->window = initialize_window(data);
	return (data);
}

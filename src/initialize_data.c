/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:19 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 17:16:17 by okrahl           ###   ########.fr       */
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
	settings->open_minimap = 1;
	settings->move_step = 5;
	settings->rotation_step = 1;
	settings->direction_line_length = 20.0;
	settings->background_color = 0xFFFFFF;
	settings->wall_color = 0x467836;
	settings->player_color = 0x0000FF;
	settings->ray_color = 0xFF0000;
	settings->tile_size = 30;
	settings->fov = 30;
	settings->num_rays = 30;
	settings->show_rays = 1;
	settings->ray_step_size = 1.0;
	settings->window_width = 1000;
	settings->window_height = 1000;
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
	//printf("player_direction: %d\n", player->player_direction);
	return (player);
}


t_temp	*initialize_temp(void)
{
	t_temp	*temp;

	temp = malloc(sizeof(t_temp));
	if (!temp)
		return (0);
	// draw_minimap
	temp->center_x = 0;
	temp->center_y = 0;
	temp->end_x = 0;
	temp->end_y = 0;
	temp->dx = 0;
	temp->dy = 0;
	temp->sx = 0;
	temp->sy = 0;
	temp->err = 0;
	temp->angle_rad = 0;
	// raycaster
	temp->current_x = 0.0f;
	temp->current_y = 0.0f;
	temp->next_x = 0.0f;
	temp->next_y = 0.0f;
	temp->step_x = 0.0f;
	temp->step_y = 0.0f;
	temp->ray_angle_rad = 0.0f;
	temp->ray_distance = 0.0f;
	temp->hit_wall = 0;
	return (temp);
}

t_rays	**initialize_rays(t_data *data)
{
	int		i;
	t_rays	**rays;

	rays = (t_rays **)malloc(sizeof(t_rays *) * data->settings->num_rays);
	if (!rays)
	{
		perror("Failed to allocate memory for rays");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (i < data->settings->num_rays)
	{
		rays[i] = (t_rays *)malloc(sizeof(t_rays));
		if (!rays[i])
		{
			perror("Failed to allocate memory for a ray");
			exit(EXIT_FAILURE);
		}
		rays[i]->length = 0.0;
		rays[i]->angle = 0;
		i++;
	}
	return (rays);
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
	data->temp = initialize_temp();
	data->rays = initialize_rays(data);
	raycaster(data);
	data->mlx = initialize_mlx(data);
	return (data);
}

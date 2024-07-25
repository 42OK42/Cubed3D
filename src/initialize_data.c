/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:19 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 20:07:41 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

t_player	*initialize_player(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->player_position = initialize_player_position(data);
	player->player_direction = initialize_player_direction(data, \
		player->player_position);
	return (player);
}

t_temp	*initialize_temp(void)
{
	t_temp	*temp;

	temp = malloc(sizeof(t_temp));
	if (!temp)
		return (0);
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
	temp->current_x = 0.0f;
	temp->current_y = 0.0f;
	temp->exited = 0;
	temp = initialize_temp2(temp);
	return (temp);
}

t_temp	*initialize_temp2(t_temp *temp)
{
	temp->next_x = 0.0f;
	temp->next_y = 0.0f;
	temp->step_x = 0.0f;
	temp->step_y = 0.0f;
	temp->ray_angle_rad = 0.0f;
	temp->ray_distance = 0.0f;
	temp->hit_wall = 0;
	temp->width = 0;
	temp->height = 0;
	temp->num_colors = 0;
	temp->chars_per_pixel = 0;
	temp->screen_x = 0;
	temp->step = 0.0f;
	temp->image_pos = 0.0f;
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

t_data	*initialize_data(char *filename, t_data *data)
{
	data->filename = filename;
	data->map_height = find_map_height_before_map(data);
	data->map_width = find_map_width(data);
	data->settings = initialize_settings();
	data->player = initialize_player(data);
	data->temp = initialize_temp();
	data->rays = initialize_rays(data);
	data->assets = initialize_assets();
	data->color_row = initialize_color_row(data);
	raycaster(data);
	data->mlx = initialize_mlx(data);
	return (data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:07:19 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/12 18:33:14 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

t_player	*initialize_player(t_data *data)
{
	t_player	*player;

	player = ft_calloc(sizeof(t_player), 1);
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

	temp = ft_calloc(sizeof(t_temp), 1);
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
	temp->previous_image = NULL;
	temp->sect_with_x = NULL;
	temp->sect_with_y = NULL;
	temp->start = NULL;
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

	rays = (t_rays **)ft_calloc(sizeof(t_rays *), data->settings->num_rays);
	if (!rays)
	{
		error_exit("Failed to allocate memory for rays", data);
	}
	i = 0;
	while (i < data->settings->num_rays)
	{
		rays[i] = (t_rays *)ft_calloc(sizeof(t_rays), 1);
		if (!rays[i])
		{
			error_exit("Failed to allocate memory for a ray", data);
		}
		rays[i]->length = 0.0;
		rays[i]->angle = 0;
		i++;
	}
	return (rays);
}

t_data	*initialize_data(char *filename, t_data *data)
{
	t_assets	*assets;

	assets = (t_assets *)ft_calloc(sizeof(t_assets), 1);
	if (!assets)
		return (NULL);
	data->assets = assets;
	data->filename = filename;
	data->map_height = find_map_height_before_map(data);
	data->map_width = find_map_width(data);
	data->settings = initialize_settings();
	data->player = initialize_player(data);
	data->temp = initialize_temp();
	data->rays = initialize_rays(data);
	initialize_assets(data);
	data->color_row = initialize_color_row(data);
	raycaster(data);
	data->mlx = initialize_mlx(data);
	return (data);
}

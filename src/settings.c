/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:09:08 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/18 19:06:44 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

t_settings	*initialize_settings(t_data *data)
{
	t_settings	*settings;

	data++;
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (NULL);
	settings->open_minimap = 1;
	settings->move_step = 2;
	settings->rotation_step = 3;
	settings->direction_line_length = 20.0;
	settings->background_color = 0xFFFFFF;
	settings->wall_color = 0x467836;
	settings->space_color = 0x808080;
	settings->player_color = 0x0000FF;
	settings->ray_color = 0xFF0000;
	settings->tile_size = 20;
	settings->fov = 90;
	settings->num_rays = 90;
	settings->show_rays = 1;
	settings->ray_step_size = 0.01;
	settings->window_width = 1000;
	settings->window_height = 1000;
	settings->max_distance = settings->tile_size / 5.0;
	settings->dist_to_proj_plane = (settings->window_height * settings->max_distance) / settings->tile_size;
	return (settings);
}
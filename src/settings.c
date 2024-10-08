/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:09:08 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/12 18:53:52 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

t_settings	*initialize_settings(void)
{
	t_settings	*settings;

	settings = ft_calloc(sizeof(t_settings), 1);
	if (!settings)
		return (NULL);
	settings->open_minimap = 1;
	settings->move_step = 2.0;
	settings->rotation_step = 1.9;
	settings->direction_line_length = 20.0;
	settings->background_color = 0xFFFFFF;
	settings->wall_color = 0x467836;
	settings->space_color = 0x808080;
	settings->player_color = 0x0000FF;
	settings->ray_color = 0xFF0000;
	settings = initialize_settings2(settings);
	return (settings);
}

t_settings	*initialize_settings2(t_settings *settings)
{
	settings->tile_size = 20;
	settings->fov = 60;
	settings->num_rays = 900;
	settings->show_rays = 1;
	settings->ray_step_size = 0.09;
	settings->window_width = 900;
	settings->window_height = 900;
	settings->max_distance = settings->tile_size / 5.0;
	settings->dist_to_proj_plane = (settings->window_height / 2) \
		/ tan((settings->fov / 2) * M_PI / 180.0);
	return (settings);
}

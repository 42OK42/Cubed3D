/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 17:08:03 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	visualizer(t_data *data)
{
	int		i;
	float	fov;
	float	angle;

	i = 0;
	fov = data->settings->fov;
	while (i < data->settings->num_rays)
	{
		data->temp->hit_wall = 0;
		angle = data->player->player_direction - (fov / 2.0) + (fov * i / (float)data->settings->num_rays);
		data->rays[i]->angle = angle;
		cast_ray(data, angle, i);
		i++;
	}
}

void	draw_fov(t_data *data)
{
	
}

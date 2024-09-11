/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 19:37:13 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	correct_for_fisheye(t_data *data)
{
	int		ray_id;

	ray_id = 0;
	while (ray_id < data->settings->num_rays)
	{
		data->rays[ray_id]->corrected_length = fix_fish_eye(data, ray_id);
		ray_id++;
	}
}

void	draw_3d_view(t_data *data)
{
	int			ray_id;
	double		wall_height;
	int			screen_x;
	int			prev_screen_x;

	draw_background(data);
	correct_for_fisheye(data);
	ray_id = 0;
	while (ray_id < data->settings->num_rays)
	{
		wall_height = (double)((data->settings->tile_size \
			/ data->rays[ray_id]->corrected_length) \
			* data->settings->dist_to_proj_plane);
		screen_x = (data->settings->window_width * ray_id) / \
			data->settings->num_rays;
		data->temp->screen_x = screen_x;
		draw_wall_slice(data, screen_x, wall_height, ray_id);
		if (ray_id > 0)
		{
			prev_screen_x = (data->settings->window_width * (ray_id - \
				1)) / data->settings->num_rays;
			fill_wall_between_rays(data, prev_screen_x, wall_height, ray_id);
		}
		ray_id++;
	}
}

void	fill_wall_between_rays(t_data *data, int prev_screen_x, \
	double wall_height, int ray_id)
{
	int	sign_x;

	if (prev_screen_x < data->temp->screen_x)
		sign_x = 1;
	else
		sign_x = -1;
	while (prev_screen_x != data->temp->screen_x + sign_x)
	{
		draw_wall_slice(data, prev_screen_x, wall_height, ray_id);
		prev_screen_x += sign_x;
	}
}

void	draw_wall_slice(t_data *data, int x, double wall_height, int ray_id)
{
	double	start_y;
	double	end_y;
	int		y;
	double	visible_start_y;
	double	visible_end_y;

	start_y = (data->settings->window_height / 2) - (wall_height / 2);
	end_y = (data->settings->window_height / 2) + (wall_height / 2);
	visible_start_y = start_y;
	visible_end_y = end_y;
	if (visible_start_y < 0)
		visible_start_y = 0;
	if (visible_end_y >= data->settings->window_height)
		visible_end_y = data->settings->window_height - 1;
	update_color_row(data, ray_id, start_y, end_y);
	y = visible_start_y;
	while (y <= visible_end_y && data->temp->exited != 1)
	{
		*(unsigned int *)(data->mlx->data_addr + (y * \
			data->mlx->size_line + x * (data->mlx->bits_per_pixel / \
			8))) = data->color_row[y];
		y++;
	}
}

void	update_color_row(t_data *data, int ray_id, int start_y, int end_y)
{
	int		**right_image;
	int		image_x;
	int		image_y;
	double	wall_height;
	int		i;

	wall_height = end_y - start_y;
	reset_color_row(data);
	right_image = get_right_image(data, ray_id);
	if (!right_image)
		return ;
	data->temp->previous_image = right_image;
	image_x = calculate_image_x(data, ray_id, get_image_width(right_image));
	data->temp->step = (long double)get_image_height(right_image) / \
		(long double)(wall_height + 1);
	data->temp->image_pos = 0;
	i = start_y;
	while (i <= end_y)
	{
		image_y = (int)data->temp->image_pos;
		if (i >= 0 && i < data->settings->window_height)
			data->color_row[i] = right_image[image_y][image_x];
		data->temp->image_pos += data->temp->step;
		i++;
	}
}

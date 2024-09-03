/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 18:10:35 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

// void	normalize_rays(t_data *data)
// {
// 	int			ray_id;
// 	long double prev1;
// 	long double prev2;
// 	long double prev3;
// 	long double post1;
// 	long double post2;
// 	long double post3;



// 	ray_id = 4;
// 	while (ray_id < data->settings->num_rays - 4)
// 	{
// 		if (prev1 < 0.015 && prev2 < 0.015 && prev3 < 0.015 && post1 < 0.015 && post2 < 0.015 && post3 < 0.015)
// 		{
// 			prev1 = data->rays[ray_id-1]->corrected_length;
// 			prev2 = data->rays[ray_id-2]->corrected_length;
// 			prev3 = data->rays[ray_id-3]->corrected_length;
// 			post1 = data->rays[ray_id+1]->corrected_length;
// 			post2 = data->rays[ray_id+2]->corrected_length;
// 			post3 = data->rays[ray_id+3]->corrected_length;
// 			data->rays[ray_id]->corrected_length = (prev1 + prev2 + prev3 + post1 + post2 + post3 + data->rays[ray_id]->corrected_length) /7;
// 			data->rays[ray_id]->corrected_length = (prev1 + prev2 + prev3 + post1 + post2 + post3 + data->rays[ray_id]->corrected_length) /7;

// 		}
// 		ray_id++;
// 	}
// 	// data->rays[ray_id]->corrected_length = data->rays[ray_id]->corrected_length + data->rays[ray_id-1]->corrected_length - data->rays[ray_id + 1]->corrected_length;
// }

void	wall_change(t_data *data, int	ray_id)
{
	if (!(fmod((double)data->rays[ray_id]->hit_x,(double)data->settings->tile_size) && fmod((double)data->rays[ray_id]->hit_y,(double)data->settings->tile_size)))
	{

		if(fmod((double)data->rays[ray_id]->hit_x,(double)data->settings->tile_size) && !(fmod((double)data->rays[ray_id+1]->hit_x,(double)data->settings->tile_size)))
		{
			data->rays[ray_id]->hinge = 1;
			data->rays[ray_id+1]->hinge = 1;
		}
		if(fmod((double)data->rays[ray_id]->hit_y,(double)data->settings->tile_size) && !(fmod((double)data->rays[ray_id+1]->hit_y,(double)data->settings->tile_size)))
		{
			data->rays[ray_id]->hinge = 1;
			data->rays[ray_id+1]->hinge = 1;
		}
	}
}

void	wall_drop(t_data *data, int	ray_id)
{
	if( (data->rays[ray_id]->length - (double)data->rays[ray_id+1]->length) < -19)
	{
		data->rays[ray_id]->hinge = 1;
		data->rays[ray_id +1]->hinge = 1;
	
	}
	if( (data->rays[ray_id +1]->length - (double)data->rays[ray_id]->length) < -19)
	{
		data->rays[ray_id]->hinge = 1;
		data->rays[ray_id +1]->hinge = 1;
	}
}

void	identify_corners(t_data *data)
{
	int	ray_id;

	ray_id = 0;
	while (ray_id < data->settings->num_rays - 1)
	{
		data->rays[ray_id]->hinge = 0;
		ray_id++;
	}
	ray_id = 0;
	data->rays[0]->hinge = 1;
	while (ray_id < data->settings->num_rays - 1)
	{
		wall_drop(data, ray_id);
		wall_change(data, ray_id);
		ray_id++;
	}
	data->rays[data->settings->num_rays-1]->hinge = 1;
}

int	count_til_hinge(t_data *data, int ray_id)
{
	int	count;
	count = 0;
	while (ray_id < data->settings->num_rays -1)
	{
		count++;
		ray_id++;
		if(data->rays[ray_id]->hinge == 1)
		{
			return(count);
		}
	}
	return(ray_id);
}

void	fill_til_hinge(t_data *data, int ray_id, int to_fill)
{
	int i;
	int down;

	down = 1;
	i = 0;
	while (i < to_fill)
	{
		i++;
		data->rays[ray_id]->length = data->rays[ray_id]->length  - ( 1 * (data->rays[ray_id]->length  - data->rays[ray_id+to_fill -down]->length ) * i / to_fill);
		ray_id++;
		down++;
	}


}

void	smooth_scaling_between_hinges(t_data *data)
{
	int	ray_id;
	int to_fill;

	ray_id = 0;
	while (ray_id < data->settings->num_rays -1)
	{
		to_fill = count_til_hinge(data, ray_id);
		fill_til_hinge(data, ray_id, to_fill);
		ray_id = ray_id + to_fill;
	}
}

void	normalize_rays(t_data *data)
{
	identify_corners(data);
	smooth_scaling_between_hinges(data);
}

void	draw_3d_view(t_data *data)
{
	int			ray_id;
	double		wall_height;
	int			screen_x;
	//          long double	corrected_distance;
	int			prev_screen_x;

	draw_background(data);
	ray_id = 0;
	// normalize_rays(data);
	while (ray_id < data->settings->num_rays)
	{
		data->rays[ray_id]->corrected_length = fix_fish_eye(data, ray_id);
		ray_id++;
	}
	ray_id = 0;
	while (ray_id < data->settings->num_rays)
	{
		// data->rays[ray_id]->corrected_length = data->rays[ray_id]->length;
		wall_height = (double)((data->settings->tile_size / data->rays[ray_id]->corrected_length) \
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
	while (y <= visible_end_y)
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
	double		wall_height;
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

int	calculate_image_x(t_data *data, int ray_id, int image_width)
{
	if ((int)data->rays[ray_id]->hit_x % data->settings->tile_size == 0)
		return (((int)data->rays[ray_id]->hit_y % data->settings->tile_size) \
			* image_width / data->settings->tile_size);
	else
		return (((int)data->rays[ray_id]->hit_x % data->settings->tile_size) \
			* image_width / data->settings->tile_size);
}

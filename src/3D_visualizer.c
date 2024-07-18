/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/18 19:23:25 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"


int **get_right_image(t_data *data, int ray_identification_number)
{
	int hit_x_int = (int)round(data->rays[ray_identification_number]->hit_x);
	int hit_y_int = (int)round(data->rays[ray_identification_number]->hit_y);
	int tile_size = data->settings->tile_size;
	float player_x = data->player->player_position[0][0];
	float player_y = data->player->player_position[0][1];

	if ((hit_x_int % tile_size) == 0)
	{
		if (hit_y_int % tile_size == 0)
		{
			if (player_y < hit_y_int && player_x < hit_x_int)
				return ( data->assets->wall_north);
			if (player_y < hit_y_int && player_x > hit_x_int)
				return ( data->assets->wall_east);
			if (player_y > hit_y_int && player_x < hit_x_int)
				return ( data->assets->wall_west);
			if (player_y > hit_y_int && player_x > hit_x_int)
				return ( data->assets->wall_south);
		}
		else
		{
			if (player_x < hit_x_int)
				return ( data->assets->wall_west);
			if (player_x > hit_x_int)
				return ( data->assets->wall_east);
		}
	}
	if ((hit_y_int % tile_size) == 0)
	{
		if (player_y < hit_y_int)
			return (data->assets->wall_north);
		if (player_y > hit_y_int)
			return ( data->assets->wall_south);
	}
	return (NULL);
}

void	reset_color_row(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->settings->window_height)
	{
		data->color_row[i] = 0;
		i++;
	}
}

/* void	update_color_row(t_data *data, int ray_identification_number, int start_y, int end_y)
{
	int		**right_image;
	int		image_x;
	int		image_y;
	int		image_height;
	int		wall_height;
	int		image_width;
	float	step;
	float	image_pos;
	int		y;

	wall_height = end_y - start_y;
	reset_color_row(data);
	// Get the right image for the current ray
	right_image = get_right_image(data, ray_identification_number);
	if (!right_image)
		return ;
	// Get the height and width of the image
	image_height = get_image_height(right_image);
	image_width = get_image_width(right_image);
	// Calculate the x position in the image based on the hit point
	image_x = ((int)data->rays[ray_identification_number]->hit_x % data->settings->tile_size) * image_width / data->settings->tile_size;
	// Calculate the step size for scaling the image to the wall height
	step = (float)image_height / (float)wall_height;
	image_pos = 0;
	y = start_y;
	// Loop through each row in the wall slice and get the corresponding color from the image
	while (y < end_y)
	{
		image_y = (int)image_pos;
		data->color_row[y] = right_image[image_y][image_x];
		image_pos += step;
		// printf("color_row[%i]: %i\n", y, data->color_row[y]);
		// printf("image_y: %i\n", image_y);
		// printf("image_x: %i\n", image_x);
		y++;
	}
} */

void	update_color_row(t_data *data, int ray_identification_number, int start_y, int end_y)
{
	int		**right_image;
	int		image_x;
	int		image_y;
	int		image_height;
	int		wall_height;
	int		image_width;
	float	step;
	float	image_pos;
	int		y;
	int		tile_size = data->settings->tile_size;

	wall_height = end_y - start_y;
	reset_color_row(data);
	// Get the right image for the current ray
	right_image = get_right_image(data, ray_identification_number);
	if (!right_image)
		return ;
	// Get the height and width of the image
	image_height = get_image_height(right_image);
	image_width = get_image_width(right_image);
	// Determine if the wall is horizontal or vertical
	if ((int)data->rays[ray_identification_number]->hit_x % tile_size == 0)
		image_x = ((int)data->rays[ray_identification_number]->hit_y % tile_size) * image_width / tile_size;
	else
		image_x = ((int)data->rays[ray_identification_number]->hit_x % tile_size) * image_width / tile_size;
	step = (float)image_height / (float)wall_height;
	image_pos = 0;
	y = start_y;
	// Loop through each row in the wall slice and get the corresponding color from the image
	while (y < end_y)
	{
		image_y = (int)image_pos;
		data->color_row[y] = right_image[image_y][image_x];
		image_pos += step;
		// printf("color_row[%i]: %i\n", y, data->color_row[y]);
		// printf("image_y: %i\n", image_y);
		// printf("image_x: %i\n", image_x);
		y++;
	}
}

void	draw_color_row(int *color_row)
{
	int	i;

	i = 0;
	while (color_row[i])
	{
		printf("color_row[%i]: %i\n", i, color_row[i]);
		i++;
	}
}

void	draw_3d_view(t_data *data)
{
	int		ray_identification_number;
	int		wall_height;
	int		screen_x;
	float	corrected_distance;
	int		prev_screen_x;

	ray_identification_number = 0;
	while (ray_identification_number < data->settings->num_rays)
	{
		corrected_distance = data->rays[ray_identification_number]->length * cos((data->rays[ray_identification_number]->angle - data->player->player_direction) * M_PI / 180);
		wall_height = (int)((data->settings->tile_size / corrected_distance) * data->settings->dist_to_proj_plane);
		if (wall_height > data->settings->window_height)
			wall_height = data->settings->window_height;
		screen_x = (data->settings->window_width / data->settings->num_rays) * ray_identification_number;
		//color = 0xFFFFFF;
		//printf("color_row[0][0]: %c\n", color_row[0][0]);
		//draw_color_row(color_row);
		draw_wall_slice(data, screen_x, wall_height, ray_identification_number);
		if (ray_identification_number > 0)
		{
			prev_screen_x = (data->settings->window_width / data->settings->num_rays) * (ray_identification_number - 1);
			fill_wall_between_rays(data, prev_screen_x, screen_x, wall_height, ray_identification_number);
		}
		ray_identification_number++;
	}
}

void	fill_wall_between_rays(t_data *data, int prev_screen_x, int screen_x, int wall_height, int ray_identification_number)
{
	int	sign_x;

	if (prev_screen_x < screen_x)
		sign_x = 1;
	else
		sign_x = -1;
	while (prev_screen_x != screen_x + sign_x)
	{
		draw_wall_slice(data, prev_screen_x, wall_height, ray_identification_number);
		prev_screen_x += sign_x;
	}
}

void	draw_wall_slice(t_data *data, int x, int wall_height, int ray_identification_number)
{
	int	start_y;
	int	end_y;
	int	y;

	start_y = (data->settings->window_height / 2) - (wall_height / 2);
	end_y = (data->settings->window_height / 2) + (wall_height / 2);
	update_color_row(data, ray_identification_number, start_y, end_y);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= data->settings->window_height)
		end_y = data->settings->window_height - 1;
	y = start_y;
	// printf("start_y %i end_y %i\n", start_y, end_y);
	// printf("x: %i\n", x);
	while (y <= end_y)
	{
		//printf("color_row[%i]: %i\n", y, color_row[i]);
		mlx_pixel_put(data->mlx->mlx, data->mlx->mlx_win, x, y, data->color_row[y]);
		y++;
	}
}

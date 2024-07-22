/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/22 16:56:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		tile_size = data->settings->tile_size;

	wall_height = end_y - start_y;
	reset_color_row(data);
	// Get the right image for the current ray
	right_image = get_right_image(data, ray_identification_number);
	//print_image(right_image);
	if (!right_image)
		return ;
	// Get the height and width of the image
	image_height = get_image_height(right_image);
	image_width = get_image_width(right_image);
	// Determine if the wall is horizontal or vertical
	if ((int)data->rays[ray_identification_number]->hit_x % tile_size == 0)
	{
		image_x = ((int)data->rays[ray_identification_number]->hit_y % tile_size) * image_width / tile_size;
		printf("hit_y: %f\n", data->rays[ray_identification_number]->hit_y);
		printf("hit_x: %f\n", data->rays[ray_identification_number]->hit_x);
		printf("image_x: %i\n", image_x);
		printf("image_width: %i\n", image_width);
		printf("tile_size: %i\n", tile_size);
	}
	else
	{
		image_x = ((int)data->rays[ray_identification_number]->hit_x % tile_size) * image_width / tile_size;
		printf("hit_y: %f\n", data->rays[ray_identification_number]->hit_y);
		printf("hit_x: %f\n", data->rays[ray_identification_number]->hit_x);
		printf("image_x: %i\n", image_x);
		printf("image_width: %i\n", image_width);
		printf("tile_size: %i\n", tile_size);
	}
	step = (float)image_height / (float)wall_height;
	image_pos = 0;
	y = start_y;
	// Loop through each row in the wall slice and get the corresponding color from the image
	while (y < end_y)
	{
		image_y = (int)image_pos;
		data->color_row[y] = right_image[image_y][image_x];
		image_pos += step;
		printf("color_row[%i]: %i\n", y, data->color_row[y]);
		printf("image_y: %i\n", image_y);
		printf("image_x: %i\n", image_x);
		y++;
	}
} */
/* int **get_right_image(t_data *data, int ray_identification_number)
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
				return (printf("north\n"), data->assets->wall_north);
			if (player_y < hit_y_int && player_x > hit_x_int)
				return (printf("east\n"), data->assets->wall_east);
			if (player_y > hit_y_int && player_x < hit_x_int)
				return (printf("west\n"), data->assets->wall_west);
			if (player_y > hit_y_int && player_x > hit_x_int)
				return (printf("south\n"), data->assets->wall_south);
		}
		else
		{
			if (player_x < hit_x_int)
				return (printf("west\n"), data->assets->wall_west);
			if (player_x > hit_x_int)
				return (printf("east\n"), data->assets->wall_east);
		}
	}
	if ((hit_y_int % tile_size) == 0)
	{
		if (player_y < hit_y_int)
			return (printf("north\n"), data->assets->wall_north);
		if (player_y > hit_y_int)
			return (printf("south\n"), data->assets->wall_south);
	}
	return (NULL);
} */

#include "../incl/cubed3D.h"

int	**get_right_image(t_data *data, int ray_id)
{
	int		hit_x_int;
	int		hit_y_int;
	float	player_x;
	float	player_y;

	hit_x_int = (int)round(data->rays[ray_id]->hit_x);
	hit_y_int = (int)round(data->rays[ray_id]->hit_y);
	player_x = data->player->player_position[0][0];
	player_y = data->player->player_position[0][1];
	if ((hit_x_int % data->settings->tile_size) == 0)
	{
		if (hit_y_int % data->settings->tile_size == 0)
		{
			if (player_y < hit_y_int && player_x < hit_x_int)
				return (data->assets->wall_north);
			if (player_y < hit_y_int && player_x > hit_x_int)
				return (data->assets->wall_east);
			if (player_y > hit_y_int && player_x < hit_x_int)
				return (data->assets->wall_west);
			if (player_y > hit_y_int && player_x > hit_x_int)
				return (data->assets->wall_south);
		}
		else
		{
			if (player_x < hit_x_int)
				return (data->assets->wall_west);
			if (player_x > hit_x_int)
				return (data->assets->wall_east);
		}
	}
	if ((hit_y_int % data->settings->tile_size) == 0)
	{
		if (player_y < hit_y_int)
			return (data->assets->wall_north);
		if (player_y > hit_y_int)
			return (data->assets->wall_south);
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

void	update_color_row(t_data *data, int ray_id, int start_y, int end_y)
{
	int		**right_image;
	int		image_x;
	int		image_y;
	int		image_height;
	int		wall_height;
	int		image_width;
	float	step;
	float	image_pos;
	int		i;

	wall_height = end_y - start_y;
	reset_color_row(data);
	right_image = get_right_image(data, ray_id);
	if (!right_image)
		return ;
	image_height = get_image_height(right_image);
	image_width = get_image_width(right_image);
	if ((int)data->rays[ray_id]->hit_x % data->settings->tile_size == 0)
		image_x = ((int)data->rays[ray_id]->hit_y % data->settings->tile_size) * image_width / data->settings->tile_size;
	else
		image_x = ((int)data->rays[ray_id]->hit_x % data->settings->tile_size) * image_width / data->settings->tile_size;
	step = (float)image_height / (float)(wall_height + 1);
	image_pos = 0;
	i = start_y;
	while (i <= end_y)
	{
		image_y = (int)image_pos;
		if (i >= 0 && i < data->settings->window_height)
			data->color_row[i] = right_image[image_y][image_x];
		image_pos += step;
		i++;
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

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (data->settings->window_height / 2))
	{
		x = 0;
		while (x < data->settings->window_width)
		{
			*(unsigned int *)(data->mlx->data_addr + (y * data->mlx->size_line + x * (data->mlx->bits_per_pixel / 8))) = data->settings->upper_background_color;
			x++;
		}
		y++;
	}
	while (y < data->settings->window_height)
	{
		x = 0;
		while (x < data->settings->window_width)
		{
			*(unsigned int *)(data->mlx->data_addr + (y * data->mlx->size_line + x * (data->mlx->bits_per_pixel / 8))) = data->settings->lower_background_color;
			x++;
		}
		y++;
	}
}

float	fix_fish_eye(t_data *data, int ray_id)
{
	float	player_angle_rad;
	float	ray_angle_rad;
	float	diff_angle;

	player_angle_rad = data->player->player_direction * M_PI / 180;
	ray_angle_rad = data->rays[ray_id]->angle * M_PI / 180 ;
	diff_angle = ray_angle_rad - player_angle_rad;
	while (diff_angle < -M_PI)
		diff_angle += 2 * M_PI;
	while (diff_angle > M_PI)
		diff_angle -= 2 * M_PI;
	return (data->rays[ray_id]->length * cos(diff_angle));
}

void	draw_3d_view(t_data *data)
{
	int		ray_id;
	int		wall_height;
	int		screen_x;
	float	corrected_distance;
	int		prev_screen_x;

	draw_background(data);
	ray_id = 0;
	while (ray_id < data->settings->num_rays)
	{
		corrected_distance = fix_fish_eye(data, ray_id);
		wall_height = (int)((data->settings->tile_size / corrected_distance) * data->settings->dist_to_proj_plane);
		screen_x = (data->settings->window_width * ray_id) / data->settings->num_rays;
		draw_wall_slice(data, screen_x, wall_height, ray_id);
		if (ray_id > 0)
		{
			prev_screen_x = (data->settings->window_width * (ray_id - 1)) / data->settings->num_rays;
			fill_wall_between_rays(data, prev_screen_x, screen_x, wall_height, ray_id);
		}
		ray_id++;
	}
}

void	fill_wall_between_rays(t_data *data, int prev_screen_x, int screen_x, int wall_height, int ray_id)
{
	int	sign_x;

	if (prev_screen_x < screen_x)
		sign_x = 1;
	else
		sign_x = -1;
	while (prev_screen_x != screen_x + sign_x)
	{
		draw_wall_slice(data, prev_screen_x, wall_height, ray_id);
		prev_screen_x += sign_x;
	}
}

void	draw_wall_slice(t_data *data, int x, int wall_height, int ray_id)
{
	int	start_y;
	int	end_y;
	int	y;
	int	visible_start_y;
	int	visible_end_y;

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
		*(unsigned int *)(data->mlx->data_addr + (y * data->mlx->size_line + x * (data->mlx->bits_per_pixel / 8))) = data->color_row[y];
		y++;
	}
}

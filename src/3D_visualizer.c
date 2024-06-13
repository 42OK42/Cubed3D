/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:04:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/06/03 17:26:34 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	draw_wall_slice(t_data *data, int x, int wall_height, int color)
{
	int	start_y;
	int	end_y;
	int	y;

	start_y = (data->settings->window_height / 2) - (wall_height / 2);
	end_y = (data->settings->window_height / 2) + (wall_height / 2);
	if (start_y < 0)
		start_y = 0;
	if (end_y >= data->settings->window_height)
		end_y = data->settings->window_height - 1;
	y = start_y;
	printf("start_y %i end_y %i\n", start_y, end_y);
	printf("x: %i\n", x);
	while (y <= end_y)
	{
		mlx_pixel_put(data->mlx->mlx, data->mlx->mlx_win, x, y, color);
		y++;
	}
}

char ***get_right_image(t_data *data, int i)
{
	int hit_x_int = (int)round(data->rays[i]->hit_x);
	int hit_y_int = (int)round(data->rays[i]->hit_y);
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

/* char	***get_right_image(t_data *data, int i)
{
	int		hit_x_int;
	int		hit_y_int;
	int		tile_size;
	float	player_x;
	float	player_y;

	hit_x_int = (int)round(data->rays[i]->hit_x);
	hit_y_int = (int)round(data->rays[i]->hit_y);
	tile_size = data->settings->tile_size;
	player_x = data->player->player_position[0][0];
	player_y = data->player->player_position[0][1];
	if ((hit_x_int % tile_size) == 0)
	{
		if (hit_y_int % tile_size == 0)
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
	if ((hit_y_int % tile_size) == 0)
	{
		if (player_y < hit_y_int)
			return (data->assets->wall_north);
		if (player_y > hit_y_int)
			return (data->assets->wall_south);
	}
	return (NULL);
} */

int	get_image_height(char ***right_image)
{
	int	i;

	i = 0;
	while (right_image[i])
		i++;
	return (i);
}

/* char	**get_color_row(t_data *data, int i, int wall_height)
{
	char	**color_row;
	char	***right_image;
	int		image_x;
	int		image_y;
	int		image_height;

	color_row = malloc(sizeof(char *) * wall_height);
	right_image = get_right_image(data, i)[0];
	image_height = get_image_height(right_image);
	image_x = (int)data->rays[i]->hit_x % data->settings->tile_size;
	image_y = 
	return (color_row);
} */

char	**get_color_row(t_data *data, int i, int wall_height)
{
	char	**color_row;
	char	***right_image;
	int		image_x;
	int		image_y;
	int		image_height;
	float	step;
	float	image_pos;
	int		y;

	// Allocate memory for the color row
	color_row = malloc(sizeof(char *) * wall_height);
	if (!color_row)
		return (NULL);
	// Get the right image for the current ray
	right_image = get_right_image(data, i);
	if (!right_image)
		return (printf("image not found\n"), NULL);
	// Get the height and width of the image
	image_height = get_image_height(right_image);
	// Calculate the x position in the image based on the hit point
	image_x = (int)data->rays[i]->hit_x % data->settings->tile_size;
	// Calculate the step size for scaling the image to the wall height
	step = (float)image_height / (float)wall_height;
	image_pos = 0;
	y = 0;
	// Loop through each row in the wall slice and get the corresponding color from the image
	while (y < wall_height)
	{
		image_y = (int)image_pos;
		color_row[y] = right_image[image_y][image_x];
		image_pos += step;
		y++;
	}
	return (color_row);
}

void	draw_color_row(char **color_row)
{
	int	i;

	i = 0;
	while (color_row[i])
	{
		printf("color_row[%i]: %s\n", i, color_row[i]);
		i++;
	}
}

void	draw_3d_view(t_data *data)
{
	int		i;
	int		wall_height;
	int		screen_x;
	int		color;
	float	corrected_distance;
	int		prev_screen_x;
	char	**color_row;

	i = 0;
	while (i < data->settings->num_rays)
	{
		corrected_distance = data->rays[i]->length * cos((data->rays[i]->angle - data->player->player_direction) * M_PI / 180);
		wall_height = (int)((data->settings->tile_size / corrected_distance) * data->settings->dist_to_proj_plane);
		if (wall_height > data->settings->window_height)
			wall_height = data->settings->window_height;
		screen_x = (data->settings->window_width / data->settings->num_rays) * i;
		color = 0xFFFFFF;
		color_row = get_color_row(data, i, wall_height);
		printf("color_row[0][0]: %c\n", color_row[0][0]);
		draw_color_row(color_row);
		draw_wall_slice(data, screen_x, wall_height, color);
		if (i > 0)
		{
			prev_screen_x = (data->settings->window_width / data->settings->num_rays) * (i - 1);
			fill_wall_between_rays(data, prev_screen_x, screen_x, wall_height, color);
		}
		i++;
	}
}

void	fill_wall_between_rays(t_data *data, int x0, int x1, int wall_height, int color)
{
	int	sign_x;

	if (x0 < x1)
		sign_x = 1;
	else
		sign_x = -1;

	while (x0 != x1 + sign_x)
	{
		draw_wall_slice(data, x0, wall_height, color);
		x0 += sign_x;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/16 16:22:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	raycaster(t_data *data)
{
	int		i;
	float	fov;
	float	angle;

	// data->temp->previous_x = data->player->player_position[0][0]; // for safety, maybe unecessary
	// data->temp->previous_y = data->player->player_position[0][0]; // for safety, maybe unecessary
	// data->temp->current_x = data->player->player_position[0][0];
	// data->temp->current_y = data->player->player_position[0][1];
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

float	find_closest_y(t_data *data)
{
	float	closest_grid_section;
	int		grid_num;

	printf("\n current x %d\n",(int)data->temp->current_x);
	printf("current y %d\n",(int)data->temp->current_y);
	grid_num = ((int)data->temp->current_y + 1) / data->settings->tile_size;
	printf(" grid_num %d\n", grid_num);
	closest_grid_section = grid_num * data->settings->tile_size;
	printf(" closest_grid y%f\n\n",closest_grid_section);
	return(closest_grid_section);
}


float	find_closest_x(t_data *data)
{
	float	closest_grid_section;
	int		grid_num;

	grid_num = ((int)data->temp->current_x + 1) / data->settings->tile_size;
	closest_grid_section = grid_num * data->settings->tile_size;
	return(closest_grid_section);
}

float find_closest_multiple(float x, int t) {
    // Calculate the nearest multiple of t
    float closest_multiple = round(x / t) * t;
    return closest_multiple;
}

t_point* get_y(t_point *var_sects, float start_x, float start_y, t_data *data, int *i)
{
	float	y_sect;

	y_sect = find_y_intercept(start_x, start_y, data->temp->current_x, data->temp->current_y, data->grid_x);
	
	var_sects[*i].x = data->grid_x;
	var_sects[*i].y = y_sect;
	*i = *i + 1;
    return (var_sects);
}

t_point* get_x(t_point *var_sects, float start_x, float start_y, t_data *data, int *i)
{
	float	x_sect;

	x_sect = find_x_intercept(start_x, start_y, data->temp->current_x, data->temp->current_y, data->grid_y);
	
	var_sects[*i].x = x_sect;
	var_sects[*i].y = data->grid_y;
	*i = *i + 1;
    return (var_sects);
}

t_point	*get_backwards_intersections(t_point *var_sects, float start_x, float start_y, t_data *data)
{
	int *i;

	i = malloc(sizeof(int));
	*i = 0;
	printf("temp curr x %f\n", data->temp->current_x);
    printf("temp curr y %f\n", data->temp->current_y);
	data->grid_x = find_closest_multiple(data->temp->current_x, data->settings->tile_size);
	data->grid_y = find_closest_multiple(data->temp->current_y, data->settings->tile_size);
	printf("grid_x %f\n", data->grid_x);
    printf("grid_y %f\n", data->grid_y);
	if (y_sect_exists(start_x, data->temp->current_x, data->grid_x))
	{
		get_y(var_sects, start_x, start_y, data, i);
		printf("x grid is hit\n");
	}
	if (x_sect_exists(start_y, data->temp->current_y, data->grid_y))
	{
		get_x(var_sects, start_x, start_y, data, i);
		printf(" y grid is hit\n");
	}
	var_sects[*i].x = -1.0f;
	var_sects[*i].y = -1.0f;
	return (var_sects);
}


t_point	*check_true_intersection(float start_x, float start_y, t_data *data)
{
	t_point	*var_sects;
	t_point	*true_sect;
	t_point	*start_p;
	t_point *hit_p; 

	hit_p = malloc(sizeof(t_point));
	start_p = malloc(sizeof(t_point));
	true_sect = malloc(sizeof(t_point));
	var_sects = malloc(sizeof(t_point) * 42);
	hit_p->x = data->temp->current_x;
	hit_p->y = data->temp->current_y;
	start_p->x = start_x;
	start_p->y = start_y;

	var_sects = get_backwards_intersections(var_sects, start_x, start_y, data);
	printf("sects[0]: x = %f, y = %f\n", var_sects[0].x, var_sects[0].y);
    printf("sects[1]: x = %f, y = %f\n", var_sects[1].x, var_sects[1].y);
    printf("sects[1]: x = %f, y = %f\n", var_sects[2].x, var_sects[2].y);
	true_sect = check_real_intersections(var_sects, true_sect, data);
	return (true_sect);
}

void	cast_ray(t_data *data, float ray_angle, int i)
{
	int		j;
	float	start_x;
	float	start_y;
	float	distance;
	t_point *true_sect;

	j = 0;
	start_x = data->player->player_position[0][0];
	start_y = data->player->player_position[0][1];
	init_ray_values(data, ray_angle);
	while (!data->temp->hit_wall)
	{
		update_ray_position(data);
		if (check_wall_hit(data))
		{
			true_sect = check_true_intersection(start_x, start_y, data);
			printf("true x %f\n",true_sect->x);
			printf("true y %f\n",true_sect->y);
			data->temp->current_x = true_sect->x;
			data->temp->current_y = true_sect->y;
			distance = sqrt(pow(data->temp->current_x - start_x, 2) + pow(data->temp->current_y - start_y, 2));
			//distance = sqrt(pow(true_sect->x - start_x, 2) + pow(true_sect->y - start_y, 2));
			
			//printf("distance: %f\n", distance);
			data->rays[i]->length = distance;
			data->rays[i]->hit_x = data->temp->current_x;
			data->rays[i]->hit_y = data->temp->current_y;
		}
		j++;
	}
}

void	init_ray_values(t_data *data, float ray_angle)
{
	data->temp->current_x = data->player->player_position[0][0];
	data->temp->current_y = data->player->player_position[0][1];
	data->temp->previous_x = data->player->player_position[0][0]; // for safety, maybe unecessary
	data->temp->previous_y = data->player->player_position[0][1]; // for safety, maybe unecessary
	if (ray_angle != 0)
	{
		data->temp->step_x = cos((ray_angle - 90) * M_PI / 180.0) * data->settings->ray_step_size;
		data->temp->step_y = sin((ray_angle - 90) * M_PI / 180.0) * data->settings->ray_step_size;
	}
	else
	{
		data->temp->step_x = 0;
		data->temp->step_y = -data->settings->ray_step_size;
	}
}


void	update_ray_position(t_data *data)
{
	data->temp->current_x += data->temp->step_x;
	data->temp->current_y += data->temp->step_y;
}

int	check_wall_hit(t_data *data)
{
	int	cell_x;
	int	cell_y;

	cell_y = (int)((data->temp->current_y) / data->settings->tile_size);
	cell_x = (int)(data->temp->current_x / data->settings->tile_size);
	if (data->temp->previous_x && data->temp->current_x >= data->temp->previous_x && data->temp->current_y >= data->temp->previous_y)
	{
		if ((int)data->temp->current_x % data->settings->tile_size == 0 && (int)data->temp->current_y % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x-1] == '1' && data->map[cell_y - 1][cell_x])
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	else if (data->temp->previous_x && data->temp->current_x <= data->temp->previous_x && data->temp->current_y >= data->temp->previous_y)
	{
		if (((int)data->temp->current_x + 1) % data->settings->tile_size == 0 && (int)data->temp->current_y % data->settings->tile_size == 0)
		{
			if (data->map[cell_y-1][cell_x] == '1' && data->map[cell_y][cell_x + 1] == '1')
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	else if (data->temp->previous_x && data->temp->current_x >= data->temp->previous_x && data->temp->current_y <= data->temp->previous_y)
	{
		if ((int)data->temp->current_x  % data->settings->tile_size == 0 && ((int)data->temp->current_y + 1) % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x-1] == '1' && data->map[cell_y + 1][cell_x])
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	else if (data->temp->previous_x && data->temp->current_x <= data->temp->previous_x && data->temp->current_y <= data->temp->previous_y)
	{
		if (((int)data->temp->current_x + 1) % data->settings->tile_size == 0 && ((int)data->temp->current_y + 1) % data->settings->tile_size == 0)
		{
			if (data->map[cell_y][cell_x+1] == '1' && data->map[cell_y + 1][cell_x])
			{
				data->temp->hit_wall = 1;
				return (1);
			}
		}
	}
	data->temp->previous_x = data->temp->current_x;
	data->temp->previous_y = data->temp->current_y;
	if (data->map[cell_y][cell_x] == '1')
	{
		data->temp->hit_wall = 1;
		return (1);
	}
	return (0);
}



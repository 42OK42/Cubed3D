/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/31 17:33:45 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void normalize_rays(t_data *data) {
    for (int i = 1; i < data->settings->num_rays - 1; i++) {
        float prev = data->rays[i - 1]->length;
        float curr = data->rays[i]->length;
        float next = data->rays[i + 1]->length;

        // Check if the current value follows the direction of change
        if (fabs(next - curr) < data->settings->ray_step_size) {
            // If the next change is minor, follow the same direction
            if (curr < prev && curr > next) {
                data->rays[i]->length = (prev + next) / 2;
            } else if (curr > prev && curr < next) {
                data->rays[i]->length = (prev + next) / 2;
            }
        }
    }
}

void	raycaster(t_data *data)
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



t_point	*check_real_intersection()
{
	t_point	*true_sect;

	calculate_intercepts(t_point p1, t_point p2)
	return (true_sect)
}

t_point *move_towards(t_point *p1, t_point *p2, float distance) {
    // Calculate the distance between the two points
    float d = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));

    // Calculate the unit direction vector components
    float ux = (p1->x - p2->x) / d;
    float uy = (p1->y - p2->y) / d;

    // Calculate the new point coordinates
    t_point *p3;
    p3->x = p2->x + distance * ux;
    p3->y = p2->y + distance * uy;

    return p3;
}

t_point	*calculate_intercepts(t_point p1, t_point p2, float *x_intercept, float *y_intercept)
{
	float	limit;
	int		i;
    // Calculate the slope (m)
    float m = (p2.y - p1.y) / (p2.x - p1.x);

    // Calculate the y-intercept (b)
    float b = p1.y - m * p1.x;

    // x-intercept (when y = 0)
    *x_intercept = -b / m;

    // y-intercept (when x = 0
	while ()
    *y_intercept = b;
}

t_point	*grid_intersections(t_point *p3, t_point *hit_p, t_point *var_sects)
{

}

t_point	*get_backwards_intersections(t_point *start_p, t_point *hit_p, t_data *data)
{
	t_point *p3;
	t_point	*var_sects;

	p3 = move_towards(start_p, hit_p, data->settings->ray_step_size * 1.1);
	var_sects = grid_intersections(p3, hit_p, var_sects);



	return (var_sects);
}

t_point	*check_true_intersection(float start_x, float start_y, t_data *data)
{
	t_point	*var_sects;
	t_point	*true_sect;
	t_point	*start_p;
	t_point *hit_p;

	hit_p->x = data->temp->current_x;
	hit_p->y = data->temp->current_y;
	start_p->x = start_x;
	start_p->y = start_y;

	var_sects = get_backwards_intersections(start_p, hit_p, data);
	true_sect = check_real_intersection();
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
			distance = sqrt(pow(data->temp->current_x - start_x, 2) + pow(data->temp->current_y - start_y, 2));
			
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



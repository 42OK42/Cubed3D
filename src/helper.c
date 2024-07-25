/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:13:34 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 15:31:30 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s", map[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_colors(char ***colors, int num_colors)
{
	int	i;

	i = 0;
	while (i < num_colors)
	{
		printf("Character: %s, Color Code: %s\n", colors[i][0], colors[i][1]);
		i++;
	}
}

void	print_colored_map_before_hex(char ***colored_map, t_temp_assets *temp)
{
	int	i;
	int	j;

	i = 0;
	while (i < temp->height)
	{
		j = 0;
		while (j < temp->width)
		{
			ft_printf("%s ", colored_map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_image(int **colored_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			ft_printf("%i ", colored_map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
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

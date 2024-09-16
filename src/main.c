/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:28 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/12 17:28:10 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (0);
	args_check(argc, argv, data);
	cubfile_check(argv[1], data);
	data = initialize_data(argv[1], data);
	if (data->settings->open_minimap)
		draw_minimap(data);
	draw_3d_view(data);
	free_ray_loop(data);
	if (game_loop(data) == 1)
		free_data(data);
	return (1);
}

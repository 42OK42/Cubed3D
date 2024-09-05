/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:28 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 20:13:05 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	args_check(argc, argv);
	cubfile_check(argv[1], data);
	data = initialize_data(argv[1], data);
	if (data->settings->open_minimap)
		draw_minimap(data);
	draw_3d_view(data);
	if (game_loop(data) == 1)
		free_data(data);
	return (1);
}

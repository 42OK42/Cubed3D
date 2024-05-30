/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:28 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/30 18:39:27 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	args_check(argc, argv);
	data = initialize_data(argv[1]);
	draw_3d_view(data);
	//print_map(data);
	game_loop(data);
	data->assets = initialize_assets(data);
	return (1);
}

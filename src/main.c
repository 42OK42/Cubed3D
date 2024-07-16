/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:28 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/31 16:21:22 by okrahl           ###   ########.fr       */
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
	draw_3d_view(data);
	//print_map(data);
	game_loop(data);
	return (1);
}

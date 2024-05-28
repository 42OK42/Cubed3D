/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:01:28 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/28 19:11:19 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	main(void)
{
	t_data	*data;

	data = initialize_data();
	draw_3d_view(data);
	//print_map(data);
	game_loop(data);
	return (1);
}

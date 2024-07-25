/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:34:27 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 15:34:34 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:13:34 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 19:13:57 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
	printf("\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:04:20 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/22 18:50:19 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	free_mlx(t_mlx *mlx)
{
	free(mlx->mlx);
	if (mlx->mlx_win_minimap)
		free(mlx->mlx_win_minimap);
	free(mlx->mlx_win);
	free(mlx);
}

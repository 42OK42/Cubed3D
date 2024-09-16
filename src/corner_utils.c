/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgacic <dgacic@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:36:07 by dgacic            #+#    #+#             */
/*   Updated: 2024/09/09 19:36:10 by dgacic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int	northeast(t_data *data)
{
	if (data->temp->previous_x && data->temp->current_x \
	>= data->temp->previous_x && data->temp->current_y \
	<= data->temp->previous_y)
		return (1);
	else
		return (0);
}

int	northwest(t_data *data)
{
	if (data->temp->previous_x && data->temp->current_x <= \
		data->temp->previous_x && data->temp->current_y <= \
		data->temp->previous_y)
		return (1);
	else
		return (0);
}

int	southwest(t_data *data)
{
	if (data->temp->previous_x && data->temp->current_x <= \
		data->temp->previous_x && data->temp->current_y >= \
		data->temp->previous_y)
		return (1);
	else
		return (0);
}

int	southeast(t_data *data)
{
	if (data->temp->previous_x && data->temp->current_x >= \
		data->temp->previous_x && data->temp->current_y >= \
		data->temp->previous_y)
		return (1);
	else
		return (0);
}

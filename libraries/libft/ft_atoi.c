/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:37:10 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/12 13:51:00 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoi(char *str)
{
	int			i;
	int			min_counter;
	long int	result;

	result = 0;
	i = 0;
	min_counter = 1;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min_counter = (-1 * min_counter);
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		result = ((result * 10) + (str[i] - '0'));
		i++;
	}
	return (result * min_counter);
}

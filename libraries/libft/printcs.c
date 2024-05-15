/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printcs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:35:31 by okrahl            #+#    #+#             */
/*   Updated: 2023/06/29 14:35:33 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

unsigned int	print_c(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

unsigned int	print_string(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

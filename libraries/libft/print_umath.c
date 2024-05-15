/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_umath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:38:35 by okrahl            #+#    #+#             */
/*   Updated: 2023/06/29 14:38:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

unsigned int	print_unbr(unsigned int n)
{
	unsigned int	len;
	long int		l;

	len = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	uputnbr(n);
	l = n;
	if (l < 0)
	{
		len++;
		l = -l;
	}
	while (l > 0)
	{
		l /= 10;
		len++;
	}
	return (len);
}

void	uputnbr(unsigned int l)
{
	if (l > 9)
	{
		uputnbr(l / 10);
	}
	ft_putchar_fd(l % 10 + '0', 1);
}

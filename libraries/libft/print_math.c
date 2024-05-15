/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:35:43 by okrahl            #+#    #+#             */
/*   Updated: 2023/06/29 14:35:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	print_nbr(int n)
{
	unsigned int	len;
	long int		l;

	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	len = 0;
	ft_putnbr_fd (n, 1);
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

void	write_base(unsigned long long nbr, char *base)
{
	unsigned long long	j;

	j = 0;
	if (nbr > (16 - 1))
	{
		j = nbr / 16;
		write_base(j, base);
	}
	write (1, &base[(nbr % 16)], 1);
}
/*
void	print_base2(unsigned long long int nbr, char *base)
{
	unsigned long long int	i;

	i = nbr;
	if (i < 0)
	{
		write(1, "-", 1);
		i = (-1 * i);
	}
	write_base(i, base);
}
*/

unsigned int	print_base(unsigned long long nbr, char *base)
{
	unsigned int	i;

	if (nbr == 0)
	{
		write(1, "0", 1);
		i = 1;
		return (i);
	}
	i = 0;
	write_base(nbr, base);
	while (nbr > 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

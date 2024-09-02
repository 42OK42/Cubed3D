/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:23:30 by okrahl            #+#    #+#             */
/*   Updated: 2023/06/08 15:23:33 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ft_printf.h"

void	ft_putnbr_fd(long int l, int fd)
{
	if (l == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l = -l;
	}
	if (l > 9)
	{
		ft_putnbr_fd(l / 10, fd);
	}
	ft_putchar_fd(l % 10 + '0', fd);
}
/*
int	main(void)
{
	ft_putnbr (42);
	return (0);
}*/

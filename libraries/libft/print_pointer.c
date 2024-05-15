/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:36:12 by okrahl            #+#    #+#             */
/*   Updated: 2023/06/29 14:36:13 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	reverse_string(char *str, size_t length)
{
	size_t	start;
	size_t	end;
	char	temp;

	start = 0;
	end = length - 1;
	write(1, "0x", 2);
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	str[length] = '\0';
}

unsigned int	print_pointer(const void *ptr, int digit)
{
	unsigned long long	address;
	int					i;
	char				str[17];

	i = 0;
	address = (unsigned long long)ptr;
	if (address == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	while (address > 0)
	{
		digit = address % 16;
		if (digit < 10)
			str[i] = '0' + digit;
		else
			str[i] = 'a' + digit - 10;
		address /= 16;
		i++;
	}
	reverse_string(str, i);
	print_string(str);
	return (strlen(str) + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:19:12 by okrahl            #+#    #+#             */
/*   Updated: 2023/07/03 13:19:25 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	unsigned int	count;
	va_list			args;

	va_start (args, format);
	if (format == NULL)
		return (-1);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			count = process_format(format, args, count);
		}
		else
		{
			print_c((char)*format);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

unsigned int	process_format(const char *format, \
	va_list args, unsigned int count)
{
	int	digit;

	digit = 0;
	if (*format == '\0')
		return (0);
	if (*format == 'c')
		count += print_c(va_arg(args, int));
	if (*format == 's')
		count += print_string(va_arg(args, char *));
	if (*format == 'i' || *format == 'd')
		count += print_nbr(va_arg(args, long int));
	if (*format == 'p')
		count += print_pointer(va_arg(args, const void *), digit);
	if (*format == 'u')
		count += print_unbr(va_arg(args, unsigned int));
	if (*format == 'x')
		count += print_base(va_arg(args, unsigned int), "0123456789abcdef");
	if (*format == 'X')
		count += print_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	if (*format == '%')
	{
		count++;
		write(1, "%", 1);
	}
	return (count);
}
/*
int	main()
{
	int ret;
	//int num = 42;
	//void *ptr = &num;

	ret=ft_printf("%x", -16);
	printf("Return value: %d\n", ret);
	return (0);
}
*/

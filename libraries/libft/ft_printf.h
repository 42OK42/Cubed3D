/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:47:54 by okrahl            #+#    #+#             */
/*   Updated: 2023/06/26 17:47:57 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int				ft_printf(const char *format, ...);
unsigned int	process_format(const char *format, va_list args, \
	unsigned int count);
unsigned int	print_c(char c);
unsigned int	print_string(char *str);
unsigned int	print_nbr(int n);
unsigned int	print_base(unsigned long long nbr, char *base);
void			print_base2(unsigned long long nbr, char *base);
void			write_base(unsigned long long nbr, char *base);
unsigned int	print_unbr(unsigned int n);
void			uputnbr(unsigned int n);
unsigned int	print_pointer(const void *ptr, int digit);
void			reverse_string(char *str, size_t length);
size_t			ft_strlen(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(long int l, int fd);

#endif

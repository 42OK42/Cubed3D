/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:09:45 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/23 14:09:54 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	get_number_length(int n)
{
	int	length;

	length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*allocate_memory(int length, int is_negative)
{
	char	*result;

	result = (char *)malloc((length + is_negative + 1) * sizeof(char));
	if (result != NULL)
		result[0] = '\0';
	return (result);
}

void	convert_number_to_string(long int n, char *result, \
int length, int is_negative)
{
	int	i;
	int	digit;

	i = 0;
	while (n > 0)
	{
		digit = n % 10;
		result[length - i - 1 + is_negative] = digit + '0';
		n /= 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char		*result;
	long int	nb;
	int			number_length;
	int			is_negative;

	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		is_negative = 1;
	else
		is_negative = 0;
	nb = n;
	if (is_negative)
		nb = -nb;
	number_length = get_number_length(nb);
	result = allocate_memory(number_length, is_negative);
	if (result == NULL)
		return (NULL);
	convert_number_to_string(nb, result, number_length, is_negative);
	if (is_negative)
		result[0] = '-';
	result[number_length + is_negative] = '\0';
	return (result);
}
/*
int	num_length(int n)
{
	int	result;

	result = 0;
	while (n > 0)
	{
		n = n / 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	int		is_neg;
	int		i;
	int		num_len;
	char	*result;

	is_neg = 0;
	i = 0;
	if (n == -2147483648)
	{
		return ("-2147483648");
	}
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	if (n == 0)
	{
		result = (char *)malloc(2 * sizeof(char));
		result[0] = '\0';
		result[1] = '\0';
		return (result);
	}
	num_len = num_length(n);
	result = (char *)malloc((num_len + is_neg + 1) * sizeof(char));
	while (n > 0)
	{
		result[num_len - i - 1 + is_neg] = ((n % 10) + 48);
		n = n / 10;
		i++;
	}
	if (is_neg == 1)
		result[0] = 45;
	result[num_len + is_neg] = '\0';
	return (result);
}

int main(void)
{
    int num = -2147483648;
    char *str = ft_itoa(num);

    printf("%s\n", str);

    free(str);

    return (0);
}
*/

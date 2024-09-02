/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:13 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/08 13:01:06 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bsd/string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
/*
int main (void)
{
	unsigned int n;
	char src[6] = "12345";
	char dest[50];
	
	n = 8;	
	printf("%zu\n", strlcpy(dest, src, n));
	//printf("%d\n", ft_strlcpy(dest, src, n));
    return(0);
}
*/

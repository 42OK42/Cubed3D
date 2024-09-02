/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:33:47 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/07 16:14:43 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_ptr;
	const char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	if (!dest_ptr && !src_ptr)
		return (NULL);
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return ((void *)dest_ptr);
}
/*
int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[20];
	unsigned int	size = 5;
	ft_memcpy(dest, src, size);
	//printf("Before: %s\n", dest, src);
	
	//printf("After: %s\n", dest, src);
	//printf("Return value: %s\n", ft_memcpy(dest, src, size));
	return (0);
}
*/

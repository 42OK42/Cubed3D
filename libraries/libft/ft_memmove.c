/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:49:10 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/07 17:53:30 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_ptr;
	const char	*src_ptr;
	size_t		i;

	i = 0;
	dest_ptr = (char *)dest;
	src_ptr = (const char *)src;
	if (!dest_ptr && !src_ptr && n)
		return (NULL);
	if ((src_ptr + n) <= dest_ptr || dest_ptr < src_ptr)
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			dest_ptr[n] = src_ptr[n];
	}
	return (dest_ptr);
}
/*
int	main(void)
{
	char	src[] = "consectetur";
	char	dest[] = "hello";
	unsigned int	size = 5;
	ft_memmove(dest, src, size);
	//printf("Before: %s\n", dest, src);
	
	//printf("After: %s\n", dest, src);
	//printf("Return value: %s\n", ft_memcpy(dest, src, size));
	return (0);
}
*/

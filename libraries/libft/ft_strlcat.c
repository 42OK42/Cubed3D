/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:47:35 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/09 19:20:17 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <bsd/string.h>
#include <string.h>

size_t	ft_strlcat(char *dest, const char *src, size_t nb)

{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (nb > 0)
	{
		while (dest[i] && i < nb)
			i++;
		while ((src[j]) && ((i + j) < nb -1))
		{
			dest[i + j] = src[j];
			j++;
		}
		if (i < nb)
			dest[i + j] = '\0';
	}
	while (src[j])
		j++;
	return (i + j);
}
/*
int main (void)
{
	char src[] = "aaaaaaaaaa";
	char dest[] = "bbbbbbbbbb";
	size_t nb = 2;
	//printf("%zu\n", ft_strlcat(dest, src, nb));
	printf("%zu\n", strlcat(dest, src, nb));
	printf("src: %s", src);
	printf("dest: %s", dest);
}
*/

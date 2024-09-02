/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:00:27 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/08 19:27:11 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *) s1;
	t2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*t1 != *t2)
		{
			if (*t1 < *t2)
				return (-1);
			else if (*t1 > *t2)
				return (1);
		}
		t1++;
		t2++;
		n--;
	}
	return (0);
}
/*
int	main (void)
{
	unsigned int n = 0;
	char s1[] = "abasdaf";
	char s2[] = "gbasdaf";
	printf("%d\n", ft_memcmp(s1, s2, n));
	printf("%d\n", memcmp(s1, s2, n));
}
*/

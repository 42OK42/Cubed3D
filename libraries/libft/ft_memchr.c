/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:25:47 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/09 15:29:18 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			return ((void *)s);
		s++;
		i++;
	}
	return (0);
}
/*
int main (void)
{
    char s [50] = "hallo";
    write(1, ft_memchr(&s, 'a', 3), 5);
    return(0);
}
*/

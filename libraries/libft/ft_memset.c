/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:32:13 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/07 16:14:39 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = (char)c;
		i++;
	}
	return (s);
}
/*
int main(void)
{
	char str[] = "Hallo";
	char	c;
	int	n;
	
	c = 'a';
	n = 3;
	printf("%s", (char*)ft_memset(str, c, n));
}
*/

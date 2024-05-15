/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:23:34 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/05 12:23:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
	return ;
}

/*
int main(void)
{
	char str[] = "Hallo";
	//char test[] = "sfdgdfgfdg";
	int	n;
	
	n = 2;
	printf("%s", ft_bzero(str, n));
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:21:39 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/08 20:03:42 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	const char	*to_find;
	const char	*str;

	to_find = little;
	str = big;
	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (to_find[j] && to_find[j] == str[i + j] && (i + j) < len)
				j++;
			if (to_find[j] == 0)
				return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}
/*
int main (void)
{
	char str[] = "ashaushdshaso";
	char to_find[] = "sh";
	printf("%s\n", ft_strnstr(str, to_find, 5));
	//printf("%d\n", strnstr(str, to_find));
}
*/

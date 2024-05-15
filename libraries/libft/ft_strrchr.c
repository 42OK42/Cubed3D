/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:44 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/09 17:53:05 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;

	temp = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
		{
			temp = s;
		}
		s++;
	}
	if (*s == (char)c)
		temp = s;
	if (temp)
		return ((char *)temp);
	return (0);
}
/*
int main (void)
{
    char *s = "hllolo";
    printf("%s\n", ft_strrchr(s, 'a'));
    return(0);
}
*/

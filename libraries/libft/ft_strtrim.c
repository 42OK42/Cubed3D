/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:12:51 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/23 14:12:57 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	get_size(char *str)
{
	unsigned int	j;

	j = 0;
	while (str[j] != '\0')
	{
		j++;
	}
	return (j);
}

int	is_set(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	size_t	len;
	size_t	start;
	size_t	end;
	size_t	trimlen;

	len = 0;
	start = 0;
	while (s1[len])
		len++;
	end = len - 1;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (is_set(s1[start], set) == 1)
		start++;
	while ((end >= start + 1) && (is_set(s1[end], set) == 1))
		end--;
	trimlen = end - start + 1;
	newstr = (char *)malloc((trimlen + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, s1 + start, trimlen);
	newstr[trimlen] = '\0';
	return (newstr);
}
/*
int main(void)
{
	char const *s1;
	const char *set;
	
	s1 = "abcdba";
	set = "acb";
	printf("%s\n",	ft_strtrim(s1, set));
	return (0);
}
*/

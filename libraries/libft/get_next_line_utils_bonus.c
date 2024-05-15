/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:52:48 by okrahl            #+#    #+#             */
/*   Updated: 2023/08/16 13:23:31 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:17 by okrahl            #+#    #+#             */
/*   Updated: 2023/08/03 16:03:01 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;
	int		i;

	p = malloc((int)nmemb * size);
	i = 0;
	if (p == NULL)
		return (NULL);
	while (i < (int)(size * nmemb))
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

char	*allocate_memory2(size_t total_length)
{
	char	*newstr;

	newstr = (char *)malloc((total_length + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	return (newstr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	char	*newstr;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = allocate_memory2(len1 + len2);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if ((char) c == 0)
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned long	i;

	i = 0;
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}

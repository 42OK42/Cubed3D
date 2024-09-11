/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 15:56:10 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"

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

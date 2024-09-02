/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:12:13 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/15 16:30:52 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

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

/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	newstr = (char *)malloc((i + j + 1) * sizeof(char));
	while (k < i)
	{
		newstr[k] = s1[k];
		k++;
	}
	k = 0;
	while (k <= j)
	{
		newstr[k + i] = s2[k];
		k++;
	}
	if (newstr == NULL)
		return (NULL);
	newstr[k + i] = '\0';
	return (newstr);
}
*/
/*
int main(void)
{
	char const *s1;
	char const *s2;
	
	s1 = "hallo";
	s2 = "Welt!";
	
	printf("%s\n",	ft_strjoin(s1, s2));
	return (0);
}
*/

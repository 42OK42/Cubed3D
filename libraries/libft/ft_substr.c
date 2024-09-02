/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:13:30 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/23 14:13:37 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	real_len;

	if (!s)
		return (NULL);
	real_len = ft_strlen(s);
	if (start >= real_len)
		return (ft_strdup(""));
	if (len >= real_len)
		substr = (char *)malloc((real_len - start + 1) * sizeof(char));
	else
		substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len && start <= real_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int main(void)
{
	char const *s;
	unsigned int start;
	size_t len;
	
	start = 9;
	len = 10;
	s = "0123456789";
	
	printf("%s\n",	ft_substr(s, start, len));
	return (0);
}
*/

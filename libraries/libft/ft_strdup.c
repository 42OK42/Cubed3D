/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:56:26 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/12 14:18:41 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc ((ft_strlen((char *)s) + 1) * sizeof (char));
	if (!p)
		return (NULL);
	while (*s != 0)
	{
		p[i] = *s;
		s++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:09:20 by okrahl            #+#    #+#             */
/*   Updated: 2023/05/12 14:13:22 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

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

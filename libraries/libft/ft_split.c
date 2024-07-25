/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:11:30 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/25 15:42:28 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word)
			in_word = 0;
		s++;
	}
	return (count);
}

void	assign_word(char **result, int word_index, \
char const *start, int length)
{
	result[word_index] = (char *)malloc((length + 1) * sizeof(char));
	if (result[word_index] == NULL)
		return ;
	ft_strncpy(result[word_index], start, length);
	result[word_index][length] = '\0';
}

char	**split_helper(char const *s, char c, int word_count)
{
	char		**result;
	char const	*start;
	int			word_index;

	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	word_index = 0;
	start = s;
	while (*s)
	{
		if (*s == c)
		{
			if (s - start > 0)
				assign_word(result, word_index++, start, s - start);
			start = s + 1;
		}
		s++;
	}
	if (s - start > 0)
		assign_word(result, word_index++, start, s - start);
	result[word_index] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int	word_count;

	if (s == NULL)
		return (NULL);
	word_count = count_words(s, c);
	return (split_helper(s, c, word_count));
}

/*
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word)
			in_word = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int			word_count;
	char		**result;
	char const	*start;
	int			word_index;

	if (s == NULL)
		return (NULL);
	word_index = 0;
	start = s;
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == c)
		{
			if (s - start > 0)
			{
				result[word_index] = (char	*)malloc((s - start + 1) * sizeof (char));
				if (result[word_index] == NULL)
					return (NULL);
				ft_strncpy(result[word_index], start, s - start);
				result[word_index][s - start] = '\0';
				word_index++;
			}
			start = s + 1;
		}
		s++;
	}
	if (s - start > 0)
	{
		result[word_index] = (char *)malloc((s - start + 1) * sizeof(char));
		if (result[word_index] == NULL)
			return (NULL);
		ft_strncpy(result[word_index], start, s - start);
		result[word_index][s - start] = '\0';
		word_index++;
	}
	result[word_index] = NULL;
	return (result);
}
*/
/*
int main(void)
{
	char const *s1;
	char c;

	s1 = "lorem ipsum dolor sit amet. Suspendisse";
	c = ' ';

	char **result = ft_split(s1, c);
	if (result != NULL)
	{
		int i = 0;
		while (result[i] != NULL)
		{
			printf("%s\n", result[i]);
			free(result[i]);
			i++;
		}
		free(result);
	}
	return 0;
}
*/

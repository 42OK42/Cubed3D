/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:36:00 by okrahl            #+#    #+#             */
/*   Updated: 2023/08/16 16:41:37 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>

char	*ft_free(char *result, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(result, buffer);
	free(result);
	return (temp);
}

char	*ft_read(int fd, char *result)
{
	char	*buffer;
	int		byte_read;

	if (!result)
		result = ft_calloc(BUFFER_SIZE, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		buffer[byte_read] = 0;
		result = ft_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (result);
}

char	*ft_next(char	*result)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (!result[i])
	{
		free(result);
		return (NULL);
	}
	j = i;
	while (result[j])
		j++;
	line = ft_calloc((j - i + 1), sizeof(char));
	i++;
	j = 0;
	while (result[i])
		line[j++] = result[i++];
	free(result);
	return (line);
}

char	*ft_line(char	*read)
{
	char	*line;
	int		i;

	i = 0;
	if (!read[i])
		return (NULL);
	while (read[i] && read[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	line[i + 1] = '\0';
	i = 0;
	while (read[i] && read[i] != '\n')
	{
		line[i] = read[i];
		i++;
	}
	line[i] = '\0';
	if (read[i])
		line[i++] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!result)
		result = NULL;
	result = ft_read(fd, result);
	if (!result)
		return (NULL);
	line = ft_line(result);
	result = ft_next(result);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;
	fd = open("t12", O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	printf("Line: %s, %i, %i", line, line[0], line[1]);
	free(line);
} */
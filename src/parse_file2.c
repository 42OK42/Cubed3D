/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/08/29 17:20:18 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

t_file_info	*initialize_file_info(void)
{
	t_file_info	*file_info;

	file_info = malloc(sizeof(t_file_info));
	if (!file_info)
		return (NULL);
	file_info->cc = -1;
	file_info->fc = -1;
	file_info->path_NO = NULL;
	file_info->path_SU = NULL;
	file_info->path_WE = NULL;
	file_info->path_EA = NULL;
	return (file_info);
}

char	*skip_empty_lines(char *file_content)
{
	while (*file_content == '\n' || *file_content == ' ' \
		|| *file_content == '\t')
		file_content++;
	return (file_content);
}

int	is_element(char *file_content)
{
	if (*file_content == 'N' || *file_content == 'S' || \
		*file_content == 'W' || *file_content == 'E' || *file_content \
		== 'F' || *file_content == 'C')
		return (1);
	return (0);
}

size_t	find_length(char *start, char *end)
{
	size_t		length;

	length = 0;
	while (start != end)
	{
		if (*start == '\n')
			break ;
		while (ft_isspace_without_newline(*start))
			start++;
		if (*start == '\n')
			break ;
		start++;
		length++;
	}
	return (length);
}

char	*copy_without_spaces(char *start, char *end)
{
	char	*path;
	size_t	path_length;
	char	*path_start;

	path_length = find_length(start, end);
	path = malloc(path_length + 1);
	if (!path)
		return (NULL);
	path_start = path;
	while (start != end)
	{
		while (ft_isspace_without_newline(*start))
			start++;
		*path = *start;
		if (*start == '\n')
			break ;
		start++;
		path++;
	}
	*path = '\0';
	return (path_start);
}

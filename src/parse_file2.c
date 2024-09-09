/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/08/29 18:50:56 by okrahl           ###   ########.fr       */
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
	file_info->path_no = NULL;
	file_info->path_su = NULL;
	file_info->path_we = NULL;
	file_info->path_ea = NULL;
	return (file_info);
}

int	is_element_color(char *file_content, t_data *data)
{
	if (*file_content == 'F')
	{
		if (data->file_info->fc != -1)
			perror_exit("Floorcolor provided multiple times");
		return (1);
	}
	if (*file_content == 'C')
	{
		if (data->file_info->cc != -1)
			perror_exit("Cellingcolor provided multiple times");
		return (1);
	}
	return (0);
}

int	is_element(char *file_content, t_data *data)
{
	if (*file_content == 'N')
	{
		if (data->file_info->path_no)
			perror_exit("NO path provided multiple times");
		return (1);
	}
	if (*file_content == 'S')
	{
		if (data->file_info->path_su)
			perror_exit("SU path provided multiple times");
		return (1);
	}
	if (*file_content == 'W')
	{
		if (data->file_info->path_we)
			perror_exit("WE path provided multiple times");
		return (1);
	}
	if (*file_content == 'E')
	{
		if (data->file_info->path_ea)
			perror_exit("EA path provided multiple times");
		return (1);
	}
	return (is_element_color(file_content, data));
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

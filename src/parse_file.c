/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/02 16:42:27 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	*copy_path(char *start, char *end)
{
	char	*path;
	char	*path_start;

	path = malloc((end - start) + 1);
	if (!path)
		return (NULL);
	path_start = path;
	while (start != end)
	{
		*path = *start;
		start++;
		path++;
	}
	*path = '\0';
	return (path_start);
}

char	*extract_path(char **file_content)
{
	char	*path_start;
	char	*path_end;
	char	*path;

	while (**file_content != 'O' && **file_content != 'E' \
		&& **file_content != 'A') 
		(*file_content)++;
	(*file_content)++;
	while (ft_isspace_without_newline(**file_content))
		(*file_content)++;
	path_start = *file_content;
	while (**file_content != '\n')
		(*file_content)++;
	path_end = *file_content;
	path = NULL;
	path = copy_path(path_start, path_end);
	return (path);
}

char	*extract_color(char **file_content)
{
	char	*path_start;
	char	*path_end;
	char	*path;

	(*file_content)++;
	path_start = *file_content;
	while (**file_content != '\n')
		(*file_content)++;
	path_end = *file_content;
	path = NULL;
	path = copy_without_spaces(path_start, path_end);
	return (path);
}

void	extract_element(t_data *data, char **file_content)
{
	if (**file_content == 'N')
	{
		(*file_content)++;
		data->file_info->path_no = extract_path(file_content);
	}
	if (**file_content == 'S')
	{
		(*file_content)++;
		data->file_info->path_su = extract_path(file_content);
	}
	if (**file_content == 'W')
	{
		(*file_content)++;
		data->file_info->path_we = extract_path(file_content);
	}
	if (**file_content == 'E')
	{
		(*file_content)++;
		data->file_info->path_ea = extract_path(file_content);
	}
	ground_floor(data, file_content);
}

char	*read_fileinfo(char *file_content, t_data *data)
{
	char	*map_start;
	char	*file_copy;

	data->file_copy = ft_strdup(file_content);
	file_copy = data->file_copy;
	map_start = skip_until_map(file_content);
	data->file_info = initialize_file_info();
	file_copy = skip_empty_lines(file_copy);
	while (map_started(file_copy) == 0 && file_copy)
	{
		file_copy = skip_empty_lines(file_copy);
		if (is_element(file_copy, data))
			extract_element(data, &file_copy);
		file_copy++;
		file_copy = skip_empty_lines(file_copy);
	}
	if (not_all_elements_provided(data))
		perror_exit("Not all elements provided before map");
	return (map_start);
}

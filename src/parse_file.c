/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/08/29 17:20:38 by okrahl           ###   ########.fr       */
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
		data->file_info->path_NO = extract_path(file_content);
	}
	if (**file_content == 'S')
	{
		(*file_content)++;
		data->file_info->path_SU = extract_path(file_content);
	}
	if (**file_content == 'W')
	{
		(*file_content)++;
		data->file_info->path_WE = extract_path(file_content);
	}
	if (**file_content == 'E')
	{
		(*file_content)++;
		data->file_info->path_EA = extract_path(file_content);
	}
	if (**file_content == 'F')
		data->file_info->fc = rgb_to_hex(extract_color(&(*file_content)));
	if (**file_content == 'C')
		data->file_info->cc = rgb_to_hex(extract_color(&(*file_content)));
}

char	*read_fileinfo(char *file_content, t_data *data)
{
	data->file_info = initialize_file_info();
	while (map_started(file_content) == 0 && file_content)
	{
		file_content = skip_empty_lines(file_content);
		if (is_element(file_content))
			extract_element(data, &file_content);
		file_content++;
		file_content = skip_empty_lines(file_content);
	}
	if (not_all_elements_provided(data))
		perror_exit("Not all elements provided");
	return (file_content);
}

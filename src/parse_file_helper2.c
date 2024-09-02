/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:09:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/02 16:42:35 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char *revert_on_line(char *file_content)
{
	if (*file_content != '\n')
		file_content--;
	while (*file_content != '\n')
	{
		file_content--;
	}
	return (file_content);
}

char	*skip_until_map(char *file_content)
{
	while (line_is_map(file_content) != 1 && *file_content != '\0')
		file_content++;
	revert_on_line(file_content);
	return (file_content);
}

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

char	*skip_until_map(char *file_content)
{
	while (map_started(file_content) != 1 && *file_content)
		file_content++;
	return (file_content);
}

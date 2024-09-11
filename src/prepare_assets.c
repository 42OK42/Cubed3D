/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:48:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/09/11 15:38:29 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	initialize_assets(t_data *data)
{
	data->assets->wall_south_path = data->file_info->path_su;
	data->assets->wall_north_path = data->file_info->path_no;
	data->assets->wall_east_path = data->file_info->path_ea;
	data->assets->wall_west_path = data->file_info->path_we;
	data->assets->wall_south = load_xpm(data->assets->wall_south_path);
	data->assets->wall_north = load_xpm(data->assets->wall_north_path);
	data->assets->wall_east = load_xpm(data->assets->wall_east_path);
	data->assets->wall_west = load_xpm(data->assets->wall_west_path);
}

int	**load_xpm(char *PATH)
{
	int				**result;
	char			**xpm_lines;
	t_temp_assets	*temp;
	char			**pixel_map;
	char			***colors;

	xpm_lines = read_xpm(PATH);
	temp = parse_header(xpm_lines);
	colors = get_colors(xpm_lines, temp->num_colors);
	pixel_map = get_pixel_map(xpm_lines, temp);
	free_two_d_array(xpm_lines);
	result = convert_to_hex(create_colored_map(colors, temp->num_colors, \
		pixel_map, temp), temp);
	free_three_d_array(colors);
	free_two_d_array(pixel_map);
	free(temp);
	return (result);
}

char	**read_xpm(char *PATH)
{
	int		fd;
	char	*line;
	char	**xpm_lines;
	int		i;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error:\n File not found\n"), NULL);
	xpm_lines = (char **)malloc(sizeof(char *) * 19);
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		xpm_lines[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	xpm_lines[i] = NULL;
	return (xpm_lines);
}

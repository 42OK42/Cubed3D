/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:48:50 by okrahl            #+#    #+#             */
/*   Updated: 2024/08/29 15:35:53 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	initialize_assets(t_data *data)
{

	data->assets = (t_assets *)malloc(sizeof(t_assets));
	if (!(data->assets))
		return;
	data->assets->wall_south_path = "images/wall_south.xpm";
	data->assets->wall_north_path = "images/wall_north.xpm";
	data->assets->wall_east_path = "images/wall_east.xpm";
	data->assets->wall_west_path = "images/wall_west.xpm";
	data->assets->wall_corner_path = "images/wall_corner.xpm";
	data->assets->wall_sectfail_path = "images/wall_sectfail.xpm";
	data->assets->wall_south = load_xpm(data->assets->wall_south_path);
	data->assets->wall_north = load_xpm(data->assets->wall_north_path);
	data->assets->wall_east = load_xpm(data->assets->wall_east_path);
	data->assets->wall_west = load_xpm(data->assets->wall_west_path);
	data->assets->wall_corner = load_xpm(data->assets->wall_corner_path);
	data->assets->wall_sectfail = load_xpm(data->assets->wall_sectfail_path);
}

int	**load_xpm(char *PATH)
{
	char			***image_before_hex;
	char			**xpm_lines;
	t_temp_assets	*temp;
	char			**pixel_map;
	char			***colors;

	xpm_lines = read_xpm(PATH);
	temp = parse_header(xpm_lines);
	colors = get_colors(xpm_lines, temp->num_colors);
	pixel_map = get_pixel_map(xpm_lines, temp);
	free_two_d_array(xpm_lines);
	image_before_hex = create_colored_map(colors, temp->num_colors, \
		pixel_map, temp);
	free_two_d_array(pixel_map);
	return (convert_to_hex(image_before_hex, temp));
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
		i++;
		line = get_next_line(fd);
	}
	xpm_lines[i] = NULL;
	return (xpm_lines);
}

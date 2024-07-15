/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:06:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/15 18:16:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

char	**read_xpm(char *PATH)
{
	int		fd;
	char	*line;
	char	**xpm_lines;
	int		i;

	fd = open(PATH, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error:\n File not found\n"), NULL);
	xpm_lines = (char **)malloc(sizeof(char *) * 64);
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

char	*find_color(char ***colors, int num_colors, char pixel)
{
	int	i;

	i = 0;
	while (i < num_colors)
	{
		if (colors[i][0][0] == pixel)
		{
			return (colors[i][1]);
		}
		i++;
	}

	return (NULL);
}

char	***get_colors(char **xpm_lines, int num_colors)
{
	char	***colors;
	int		i;

	colors = malloc_color_entries(num_colors);
	if (!colors)
		return (NULL);

	i = 0;
	while (i < num_colors)
	{
		colors[i][0][0] = xpm_lines[i + 4][1];
		colors[i][0][1] = '\0';
		ft_strncpy(colors[i][1], &xpm_lines[i + 4][4], 8);
		colors[i][1][8] = '\0';
		i++;
	}
	return (colors);
}

t_temp_assets	*parse_header(char **xpm_lines)
{
	t_temp_assets	*temp;

	temp = (t_temp_assets *)malloc(sizeof(t_temp_assets));
	temp->num_colors = ft_atoi(&xpm_lines[3][7]);
	temp->chars_per_pixel = ft_atoi(&xpm_lines[3][9]);
	temp->width = (ft_atoi(&xpm_lines[3][1]));
	temp->height = (ft_atoi(&xpm_lines[3][4]));
	return (temp);
}

char	**get_pixel_map(char **xpm_lines, t_temp_assets *temp)
{
	char	**pixel_map;
	int		i;

	pixel_map = malloc_pixel_map(temp->height, temp->width);
	if (!pixel_map)
		return (NULL);

	i = 0;
	while (i < temp->height)
	{
		ft_strncpy(pixel_map[i], &xpm_lines[i + 5 + temp->num_colors][1], temp->width);
		pixel_map[i][temp->width] = '\0';
		i++;
	}
	return (pixel_map);
}

char	***create_colored_map(char ***colors, int num_colors, char **pixel_map, t_temp_assets *temp)
{
	char	***map;
	int		i;
	int		j;
	char	*color;

	map = malloc_color_map(temp->height, temp->width);
	if (!map)
		return (NULL);
	i = 0;
	while (i < temp->height)
	{
		j = 0;
		while (j < temp->width)
		{
			color = find_color(colors, num_colors, pixel_map[i][j]);
			if (color)
			{
				ft_strncpy(map[i][j], color, 8);
				map[i][j][8] = '\0';
			}
			j++;
		}
		i++;
	}
	return (map);
}

int	**convert_to_hex(char ***image_before, t_temp_assets *temp)
{
	int	i;
	int	j;
	int	**image_result;

	i = 0;
	while (i < temp->height)
	{
		j = 0;
		while (j < temp->width)
		{
			image_result[i][j] = ft_atoi_base(image_before[i][j], 16);
			j++;
		}
		i++;
	}
	return (image_result);
}

int	**load_xpm(char *PATH)
{
	char			***image_before_hex;
	char			**xpm_lines;
	t_temp_assets	*temp;
	char			**pixel_map;
	char			***colors;
	int				**image_result;

	xpm_lines = read_xpm(PATH);
	temp = parse_header(xpm_lines);
	colors = get_colors(xpm_lines, temp->num_colors);
	pixel_map = get_pixel_map(xpm_lines, temp);
	image_before_hex = create_colored_map(colors, temp->num_colors, pixel_map, temp);
	image_result = convert_to_hex(image_before_hex, temp);
	print_colored_map_before_hex(image_before_hex, temp);
	return (image_result);
}

t_assets	*initialize_assets(void)
{
	t_assets	*assets;

	assets = (t_assets *)malloc(sizeof(t_assets));
	if (!assets)
		return (NULL);
	assets->ceiling_color = 0x000000;
	assets->floor_color = 0x000000;
	assets->wall_south_path = "images/wall_south.xpm";
	assets->wall_north_path = "images/wall_north.xpm";
	assets->wall_east_path = "images/wall_east.xpm";
	assets->wall_west_path = "images/wall_west.xpm";
	assets->wall_south = load_xpm(assets->wall_south_path);
	assets->wall_north = load_xpm(assets->wall_north_path);
	assets->wall_east = load_xpm(assets->wall_east_path);
	assets->wall_west = load_xpm(assets->wall_west_path);
	return (assets);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:06:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/30 19:35:10 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	skip_line(int fd)
{
	char	ch;

	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\n')
			break ;
	}
}

int	parse_header()
{
	int	i;
	
	i = 3;
	data->temp->width = 0;
	data->temp->height = 0;
	data->temp->num_colors = 0;
	data->temp->chars_per_pixel = 0;
	while (data->temp->header[i] != ' ' && data->temp->header[i] != '\0')
	{
		data->temp->width = data->temp->width * 10 + (data->temp->header[i] - '0');
		i++;
	}
	i++;
	while (data->temp->header[i] != ' ' && data->temp->header[i] != '\0')
	{
		data->temp->height = data->temp->height * 10 + (data->temp->header[i] - '0');
		i++;
	}
	i++;
	while (data->temp->header[i] != ' ' && data->temp->header[i] != '\0')
	{
		data->temp->num_colors = data->temp->num_colors * 10 + (data->temp->header[i] - '0');
		i++;
	}
	i++;
	while (data->temp->header[i] != ' ' && data->temp->header[i] != '\0')
	{
		data->temp->chars_per_pixel = data->temp->chars_per_pixel * 10 + (data->temp->header[i] - '0');
		i++;
	}
	return 0;
}

void	read_colors(int fd, char **colors, int index, t_data *data)
{
	if (index >= data->temp->num_colors)
		return;
	colors[index] = (char *)malloc((2 + 7) * sizeof(char)); // 2 for the character(s), 7 for the color code
	data->temp->color_line = get_next_line(fd);
	int i = 0;
	while (data->temp->color_line[i] != '\0')
	{
		colors[index][i] = data->temp->color_line[i];
		i++;
	}
	colors[index][i] = '\0';
	read_colors(fd, colors, index + 1, data);
}

void	read_pixels(int fd, char **pixels, int index, t_data *data)
{
	if (index >= data->temp->height)
		return;
	pixels[index] = (char *)malloc((data->temp->width + 1) * sizeof(char));
	data->temp->pixel_line = get_next_line(fd);
	int i = 0;
	while (data->temp->pixel_line[i] != '\0')
	{
		pixels[index][i] = data->temp->pixel_line[i];
		i++;
	}
	pixels[index][i] = '\0';
	read_pixels(fd, pixels, index + 1, data);
}

char	**load_xpm(const char *file_path, t_data *data)
{
	int		fd;
	int		i;
	char	**colors;
	char	**pixels;

	write(1, "Loading xpm file\n", 17);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	skip_line(fd);
	skip_line(fd);
	data->temp->header = get_next_line(fd);
	parse_header(data);
	colors = (char **)malloc(data->temp->num_colors * sizeof(char *));
	pixels = (char **)malloc(data->temp->height * sizeof(char *));
	i = 0;
	while (i < data->temp->num_colors)
	{
		colors[i] = get_next_line(fd);
		printf("colors[%i]: %s\n", i, colors[i]);
		i++;
	}
	i = 0;
	write(1, "test4\n", 6);
	printf("data->temp->height: %d\n", data->temp->height);
	while (i < data->temp->height)
	{
		pixels[i] = get_next_line(fd);
		i++;
	}
	write(1, "test5\n", 6);
	close(fd);
	return (merge_colors_and_pixels(pixels, colors, data));
}

char	**merge_colors_and_pixels(char **pixels, char **colors, t_data *data)
{
	char		**merged_colors;
	int		i;
	int		j;

	write(1, "test5\n", 6);
	merged_colors = (char **)malloc(data->temp->height * sizeof(char *));
	if (!merged_colors)
		return (NULL);
	i = 0;
	write(1, "test6\n", 6);
	while (i < data->temp->height)
	{
		merged_colors[i] = (char *)malloc((data->temp->width + 1) * sizeof(char));
		if (!merged_colors[i])
			return (NULL);
		j = 0;
		printf ("test[%i]\n", i);
		while (j < data->temp->width)
		{
			write(1, "test6.1\n", 8);
			printf("pixels[%i][%i]: %c\n", i, j, pixels[i][j]);
			merged_colors[i][j] = *get_color_value(pixels[i][j], colors, data);
			j++;
		}
		merged_colors[i][j] = '\0'; // Nullterminierung der Zeichenkette
		printf("merged_colors[%i]: %s\n", i, merged_colors[i]);
		i++;
	}
	write(1, "test7\n", 6);
	return (merged_colors);
}


char	*get_color_value(char c, char **colors, t_data *data)
{
	int	i;

	i = 0;
	write (1, "test8\n", 6);
	while (i < data->temp->num_colors)
	{
		if (colors[i][1] == c)
		{
			printf("colors[%i]: %s\n", i, colors[i]);
			return (colors[i]);
		}
		i++;
	}
	printf("c: %c\n", c);
	return (NULL);
}


t_assets	*initialize_assets(t_data *data)
{
	t_assets	*assets;

	assets = (t_assets *)malloc(sizeof(t_assets));
	if (!assets)
		return (NULL);
	write(1, "Initializing assets\n", 21);
	assets->ceiling_color = 0x000000;
	assets->floor_color = 0x000000;
	assets->wall_south_path = "images/wall_south.xpm";
	assets->wall_north_path = "images/wall_north.xpm";
	assets->wall_east_path = "images/wall_east.xpm";
	assets->wall_west_path = "images/wall_west.xpm";
	assets->wall_south = load_xpm(assets->wall_south_path, data);
	assets->wall_north = load_xpm(assets->wall_north_path, data);
	assets->wall_east = load_xpm(assets->wall_east_path, data);
	assets->wall_west = load_xpm(assets->wall_west_path, data);

	print_map(assets->wall_south);

	return (assets);
}


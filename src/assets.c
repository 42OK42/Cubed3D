/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:06:17 by okrahl            #+#    #+#             */
/*   Updated: 2024/05/30 20:36:56 by okrahl           ###   ########.fr       */
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

char	***get_colors(char **xpm_lines, int num_colors)
{
	char	***colors;
	int		i;
	int		j;

	colors = (char ***)malloc(sizeof(char **) * num_colors);
	if (!colors)
		return (NULL);

	i = 0;
	while (i < num_colors)
	{
		colors[i] = (char **)malloc(sizeof(char *) * 2);
		if (!colors[i])
		{
			j = 0;
			while (j < i)
			{
				free(colors[j]);
				j++;
			}
			free(colors);
			return (NULL);
		}
		colors[i][0] = (char *)malloc(sizeof(char) * 2);
		colors[i][1] = (char *)malloc(sizeof(char) * 8);
		if (!colors[i][0] || !colors[i][1])
		{
			j = 0;
			while (j <= i)
			{
				if (colors[j][0])
					free(colors[j][0]);
				if (colors[j][1])
					free(colors[j][1]);
				free(colors[j]);
				j++;
			}
			free(colors);
			return (NULL);
		}
		colors[i][0][0] = xpm_lines[i + 4][1];
		colors[i][0][1] = '\0';
		ft_strncpy(colors[i][1], &xpm_lines[i + 4][4], 7);
		colors[i][1][7] = '\0';
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

	pixel_map = (char **)malloc(sizeof(char *) * temp->height);
	if (!pixel_map)
		return (NULL);
	i = 0;
	while (i < temp->height)
	{
		pixel_map[i] = (char *)malloc(sizeof(char) * temp->width);
		ft_strncpy(pixel_map[i], &xpm_lines[i + 5 + temp->num_colors][1], temp->width);
		i++;
	}
	return (pixel_map);
}

char ***create_colored_map(char ***colors, int num_colors, char **pixel_map, t_temp_assets *temp)
{
	char ***map;
	int i, j;

	// Speicher für die neue Karte allokieren
	map = (char ***)malloc(sizeof(char **) * temp->height);
	if (!map)
		return NULL;

	// Schleife über jede Zeile der Pixelkarte
	i = 0;
	while (i < temp->height)
	{
		// Speicher für jede Zeile der neuen Karte allokieren
		map[i] = (char **)malloc(sizeof(char *) * temp->width);
		if (!map[i])
		{
			// Speicher freigeben bei Fehler
			int k = 0;
			while (k < i)
			{
				free(map[k]);
				k++;
			}
			free(map);
			return NULL;
		}

		// Schleife über jedes Zeichen der Pixelkarte
		j = 0;
		while (j < temp->width)
		{
			int k = 0;

			// Suche den Farbcode für das aktuelle Zeichen
			while (k < num_colors)
			{
				if (colors[k][0][0] == pixel_map[i][j])
				{
					// Speicher für den Farbcode allokieren
					map[i][j] = (char *)malloc(sizeof(char) * 8); // '#' + 6 hex chars + '\0'
					if (!map[i][j])
					{
						// Speicher freigeben bei Fehler
						int l = 0;
						while (l <= i)
						{
							int m = 0;
							while (m < temp->width)
							{
								if (map[l][m])
									free(map[l][m]);
								m++;
							}
							free(map[l]);
							l++;
						}
						free(map);
						return NULL;
					}
					// Kopiere den Farbcode in die neue Karte
					ft_strncpy(map[i][j], colors[k][1], 7);
					map[i][j][7] = '\0'; // Sicherstellen, dass die Zeichenkette nullterminiert ist
					break;
				}
				k++;
			}
			j++;
		}
		i++;
	}

	return map;
}


char	***load_xpm(char *PATH, t_data *data)
{
	char	***image_result;
	char			**xpm_lines;
	t_temp_assets	*temp;
	char			**pixel_map;
	char			***colors;

	printf("data->filename: %s\n", data->filename);
	xpm_lines = read_xpm(PATH);
	temp = parse_header(xpm_lines);
	colors = get_colors(xpm_lines, temp->num_colors);
	pixel_map = get_pixel_map(xpm_lines, temp);
	//printf("pixel_map[0]: %s\n", pixel_map[0]);
	print_colors(colors, temp->num_colors);
	//print_map(pixel_map);
	image_result = create_colored_map(colors, temp->num_colors, pixel_map, temp);
	print_colored_map(image_result, temp);
	return (image_result);
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

	return (assets);
}


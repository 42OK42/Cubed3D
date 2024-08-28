/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:13:34 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/15 18:11:54 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s", map[i]);
		i++;
	}
	ft_printf("\n");
}
void	print_colors(char ***colors, int num_colors)
{
	int	i;

	i = 0;
	while (i < num_colors)
	{
		printf("Character: %s, Color Code: %s\n", colors[i][0], colors[i][1]);
		i++;
	}
}

// char	*ft_strncpy(char *dest, const char *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n && src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 	{
// 		dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

void	print_colored_map_before_hex(char ***colored_map, t_temp_assets *temp)
{
	int	i;
	int	j;

	i = 0;
	while (i < temp->height)
	{
		j = 0;
		while (j < temp->width)
		{
			ft_printf("%s ", colored_map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_image(int **colored_map)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		ft_printf("%s ", colored_map[i]);
		ft_printf("\n");
		i++;
	}
}

int	get_image_height(int **right_image)
{
	int	i;

	i = 0;
	while (right_image[i])
		i++;
	return (i);
}

int	get_image_width(int **right_image)
{
	int	i;

	i = 0;
	while (right_image[0][i])
		i++;
	return (i);
}
int	ft_atoi_base(char *str, int base)
{
	int i;
	int res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * base + str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			res = res * base + str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			res = res * base + str[i] - 'a' + 10;
		i++;
	}
	return (res * sign);
}

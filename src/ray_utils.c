/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/16 16:22:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

int     y_sect_exists(long double x1, long double x2, long double x_value)
{
    // Check if x_value is between x1 and x2
    if ((x_value >= x1 && x_value <= x2) || (x_value >= x2 && x_value <= x1))
        return (1);
    else
        return (0);
}

long double   find_y_intercept(long double x1, long double y1, long double x2, long double y2, long double x_value)
{
    // Calculate the slope (m)
    long double m = (y2 - y1) / (x2 - x1);
    
    // Calculate the y-intercept (b)
    long double b = y1 - m * x1;
    
    // Calculate the y value at the given x_value
    long double y_value = m * x_value + b;
    
    return (y_value);
}

long double   calculate_slope(long double x1, long double y1, long double x2, long double y2)
{
    return ((y2 - y1) / (x2 - x1));
}

long double   find_y_intercept_0(long double x1, long double y1, long double x2, long double y2)
{
    // Calculate the slope (m)
    long double m = (y2 - y1) / (x2 - x1);
    
    // Calculate the y-intercept (b) using y = mx + b -> b = y - mx
    long double b = y1 - m * x1;
    
    return b;
}

long double   find_x_intercept(long double x1, long double y1, long double x2, long double y2, long double grid)
{
    long double   x_intercept;
    long double   m = calculate_slope(x1, y1, x2, y2);
    long double   b = find_y_intercept_0(x1, y1, x2, y2);

    if (x1 == x2)
        return (x1);
    x_intercept = (grid - b) / m;
    return (x_intercept);
}

int     x_sect_exists(long double y1, long double y2, long double d)
{
    if ((d >= y1 && d <= y2) || (d >= y2 && d <= y1))
        return 1;
    else
        return 0;
}
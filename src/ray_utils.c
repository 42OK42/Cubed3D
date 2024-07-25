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

int     y_sect_exists(float x1, float x2, float x_value)
{
    // Check if x_value is between x1 and x2
    if ((x_value >= x1 && x_value <= x2) || (x_value >= x2 && x_value <= x1))
        return (1);
    else
        return (0);
}

float   find_y_intercept(float x1, float y1, float x2, float y2, float x_value)
{
    // Calculate the slope (m)
    float m = (y2 - y1) / (x2 - x1);
    
    // Calculate the y-intercept (b)
    float b = y1 - m * x1;
    
    // Calculate the y value at the given x_value
    float y_value = m * x_value + b;
    
    return (y_value);
}

float   calculate_slope(float x1, float y1, float x2, float y2)
{
    return ((y2 - y1) / (x2 - x1));
}

float   find_y_intercept_0(float x1, float y1, float x2, float y2)
{
    // Calculate the slope (m)
    float m = (y2 - y1) / (x2 - x1);
    
    // Calculate the y-intercept (b) using y = mx + b -> b = y - mx
    float b = y1 - m * x1;
    
    return b;
}

float   find_x_intercept(float x1, float y1, float x2, float y2, float grid)
{
    float   x_intercept;
    float   m = calculate_slope(x1, y1, x2, y2);
    float   b = find_y_intercept_0(x1, y1, x2, y2);

    x_intercept = (grid - b) / m;
    return (x_intercept);
}

int     x_sect_exists(float y1, float y2, float d)
{
    if ((d >= y1 && d <= y2) || (d >= y2 && d <= y1))
        return 1;
    else
        return 0;
}
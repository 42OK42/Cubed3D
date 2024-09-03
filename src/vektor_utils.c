/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:37 by okrahl            #+#    #+#             */
/*   Updated: 2024/07/16 16:22:50 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cubed3D.h"

// calculate_map_end(t_point *start, t_point *P2, t_data *data)
// {
//     t_point *map_end;

//     map_end = malloc(sizeof(t_point));


//     return (map_end);
// }

t_point *calculate_all_sects(start, map_end, data)
{
    t_point *sect_list;

    sect_list = malloc(sizeof(t_point) * 42 ); // care, hardcoded value!!!!
    
    return (sect_list);
}

// t_point *find_first_true_sect(sect_list, data)
// {

//     return ();
// }

t_point	*check_true_intersection(t_point *start, t_point *P2, t_data *data)
{
    t_point *true_sect;
    t_point *map_end;
    t_point *sect_list;

    true_sect = malloc(sizeof(t_point));
    map_end->x = calculate_map_end(start, P2, data);
    sect_list = calculate_all_sects(start, map_end, data);
    true_sect = find_first_true_sect(sect_list, data);

    return (true_sect);
}
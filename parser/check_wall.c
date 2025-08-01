/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 02:19:18 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/01 02:47:41 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"


int check_walls(t_file *file)
{
    int x = 0;
    int y;
    int len = ft_strlen(file->map[0]) - 1;
    while (x < len)
    {
        if (file->map[0][x] != '1' && file->map[0][x] != ' ')
        {
            return -1;
        }
        x++;
    }
   
    x = 0;
    len = ft_strlen(file->map[file->map_height - 1]);
    while (x < len - 1)
    {
        if (file->map[file->map_height - 1][x] != '1' && file->map[file->map_height - 1][x] != ' ')
            return -1;
        x++;
    }
    y = 1;
    while (y < file->map_height - 1)
    {
        len = ft_strlen(file->map[y]) - 1;
        if (len == 0)
            return -1;
        if (file->map[y][0] != '1' && file->map[y][0] != ' ')
            return -1;
        if (file->map[y][len - 1] != '1' && file->map[y][len - 1] != ' ')
            return -1;
        y++;
    }
    return 0;
}

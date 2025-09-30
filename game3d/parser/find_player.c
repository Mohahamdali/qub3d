/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:57:36 by mhamdali          #+#    #+#             */
/*   Updated: 2025/09/27 15:13:00 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"


static void check_duplicate (int found, t_garbage *gc)
{
      if (found > 1)
      {
        ft_putstr_fd("Error\nMore player in map\n",2),
        cleanup_grb_cltr(gc);
        exit(1);
      }
    if (found == 0)
    {
        ft_putstr_fd("Error\nNO player in map\n",2),
        cleanup_grb_cltr(gc);
        exit(1);
    }
}

void find_player_in_map(char **map, t_app *p, t_garbage *gc)
{
    int i = 0;
    int j;

    int found = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (map[i][j] == 'N')
                {
                    p ->angle = M_PI_2;
                    p->dir_x = 0;
                    p->dir_y = -1;
                }
                else if (map[i][j] == 'S')
                {
                    p->angle = 3 * M_PI_2;
                    p->dir_x = 0;
                    p->dir_y = 1;
                }
                else if (map[i][j] == 'E')
                {
                    p->angle = 0; 
                    p->dir_x = 1;
                    p->dir_y = 0;
                }
                else if (map[i][j] == 'W')
                {
                    p->angle = M_PI; 
                    p->dir_x = -1;
                    p->dir_y = 0;
                }
                p->player_x = (j + 0.5f) * TILE;  // pixels
                p->player_y = (i + 0.5f) * TILE;  // pixels
                found++;
            }
            j++;
        }
        i++;
    }
    check_duplicate(found, gc);
}

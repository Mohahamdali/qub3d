/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:02:13 by manter            #+#    #+#             */
/*   Updated: 2025/10/09 20:24:32 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void build_3d(t_file *file, int var, float ray_angle)
{
    float	wall_height;
	int		start_y;
	int		end_y;
	int		j;
    
	wall_height = (float)file->img.h / file->app.algo.final_dist;
    
	start_y = (file->img.h  / 2) - (wall_height / 2);
	end_y = start_y + wall_height;
	j = 0;
    while (j < start_y)
		put_px(&file->img, var, j++, CEILING_COLOR);
    file ->start_draw = j;
    file ->end_draw = end_y;
    main_draw(file,&file ->app, var, ray_angle);
    j = file->end_draw;
    while (j < file->img.h)
        put_px(&file->img, var, j++, FLOOR_COLOR);
}

void ft_building(t_file *file, float ray_angle, int var)
{
    build_3d(file,var ,ray_angle);
}  
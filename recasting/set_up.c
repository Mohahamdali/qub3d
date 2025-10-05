/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 02:53:19 by manter            #+#    #+#             */
/*   Updated: 2025/10/05 13:27:09 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void ft_dda_init(t_app *app, float ray_angle)
{
    app->algo.x_pos = (int) (app->player_y/ (float)TILE);
    app->algo.y_pos = (int) (app->player_x / (float)TILE);
    app->algo.x_ray_length = fabs(1 / cos(ray_angle));
	app->algo.y_ray_length = fabs(1 / sin(ray_angle));
    app->algo.x_step_sign = 1;
    app->algo.y_step_sign = 1;
}

static  void ft_chek_dir(t_app *app, float ray_angle)
{
    
    if (cos(ray_angle) < 0)
    {
        app->algo.x_step_sign = -1;
        app->algo.hori_dist = ((app->player_y / (float)TILE) - \
		app->algo.x_pos) * app->algo.x_ray_length;
	}
    else 
    {
        app->algo.hori_dist = (app->algo.x_pos + 1.0 - \
		(app->player_y / (float)TILE)) * app->algo.x_ray_length;
    }
    if (sin(ray_angle) < 0)
    {
        app->algo.y_step_sign = -1;
        app->algo.vert_dist = ((app->player_x / (float)TILE) - \
		app->algo.y_pos) * app->algo.y_ray_length;
    }
    else 
    {
        app->algo.vert_dist = (app->algo.y_pos + 1.0 - \
		(app->player_x / (float)TILE)) * app->algo.y_ray_length;
    }
}
static void ft_calc_dist(t_file *file, float ray_angle)
{
    while(1)
    {
        if (file->app.algo.hori_dist < file->app.algo.vert_dist)
        {
            file->app.algo.hori_dist += file->app.algo.x_ray_length;
            file->app.algo.x_pos += file->app.algo.x_step_sign;
            file->app.algo.wall_side = 0;
        }
        else 
        {
            file->app.algo.vert_dist += file->app.algo.y_ray_length;
            file->app.algo.y_pos += file->app.algo.y_step_sign;
            file->app.algo.wall_side = 1;
        }
        if (ft_is_wall(file->app.algo.y_pos, file->app.algo.x_pos, file))
            break;
    }
    
    if (!file->app.algo.wall_side)
        file->app.algo.final_dist = file->app.algo.hori_dist - file->app.algo.x_ray_length;
    else
        file->app.algo.final_dist = file->app.algo.vert_dist - file->app.algo.y_ray_length;

    file->app.algo.final_dist *= cos(file->app.angle - ray_angle);
}
static void cast_ray_stop_at_wall(t_file *file, float ray_angle , int var)
{
    ft_dda_init(&file->app, ray_angle);
    ft_chek_dir(&file->app, ray_angle);
    ft_calc_dist(file, ray_angle);
    ft_building(file, ray_angle , var);
     
}

static void draw_fov_cone(t_file *file)
{
    float angle_incre =  PI / 3 / file->img.w;
    float ray_angle   = file->app.angle - (PI / 6);

    int var = 0;
    while (var < file->img.w)
    {
        cast_ray_stop_at_wall(file, ray_angle, var);
        // Use RAW final_dist (tiles) to get hit point in PIXELS
        // float dir_x = cosf(ray_angle);
        // float dir_y = sinf(ray_angle);
        // float t_pixels = file->app.algo.final_dist * (float)TILE;

        // int hit_px = (int)(file->app.player_x + dir_x * t_pixels);
        // int hit_py = (int)(file->app.player_y + dir_y * t_pixels);

        // draw_line(&file->img,
        //           (int)file->app.player_x, (int)file->app.player_y,
        //           hit_px, hit_py,
        //           file->app.algo.wall_side ? 0x00008800 : 0x0000AA00);
        ray_angle += angle_incre;
        var++;
    }
}

int draw_frame(t_file *file)
{
    // Paint background white
    fill_rect(&file->img, 0, 0, file->img.w, file->img.h, 0x00FFFFFF);
    // Draw map cells
    // for (int my = 0; my < MAP_H; ++my) {
    //     for (int mx = 0; mx < MAP_W ; ++mx) {
    //         int sx = mx * TILE;
    //         int sy = my * TILE;
    //         if (file->map[my][mx] == '1') {
    //             // Wall = black
    //             fill_rect(&file->img, sx, sy, TILE, TILE, 0x00000000);
    //         }
    //     }
    // }
    // draw_player(&file->img,  file->app.player_x, file->app.player_y, 8, 0x00FF0000); // red point, radius 5
    draw_fov_cone(file);  //// this is added <---->
    mlx_put_image_to_window(file->app.mlx, file->app.win, file->img.ptr, 0, 0);
    return 0;
}

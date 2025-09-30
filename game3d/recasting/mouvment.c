/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:16:22 by manter            #+#    #+#             */
/*   Updated: 2025/09/27 14:29:50 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../qub3d.h"

// check if a position is inside a wall
static int is_wall(int x, int y, t_file *file)
{
    int grid_x = x / (float)TILE;
    int grid_y = y / (float)TILE;
    if (file->map[grid_y][grid_x] == 1) // 1 = wall
        return (1);
    return (0);
}
int key_hook(int key, t_file *file)
{
    float new_x, new_y;

    if (key == 65307) // ESC
        exit(0);

    if (key == 65361)
        file->app.angle -= ROT_STEP;

    if (key == 65363)
        file->app.angle += ROT_STEP;

    if (key == 119) {
        new_x = file->app.player_x + cos(file->app.angle) * MOVE_STEP;
        new_y = file->app.player_y + sin(file->app.angle) * MOVE_STEP;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x += cos(file->app.angle) * MOVE_STEP;
            file->app.player_y += sin(file->app.angle) * MOVE_STEP;
        }
    }
    if (key == 115) {
        new_x = file->app.player_x - cos(file->app.angle) * MOVE_STEP;
        new_y = file->app.player_y - sin(file->app.angle) * MOVE_STEP;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x -= cos(file->app.angle) * MOVE_STEP;
            file->app.player_y -= sin(file->app.angle) * MOVE_STEP;
        }
    }

    if (key == 97) {
        new_x = file->app.player_x + cos(file->app.angle - M_PI_2) * MOVE_STEP;
        new_y = file->app.player_y + sin(file->app.angle - M_PI_2) * MOVE_STEP;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x += cos(file->app.angle - M_PI_2) * MOVE_STEP;
            file->app.player_y += sin(file->app.angle - M_PI_2) * MOVE_STEP;
        }
    }

    if (key == 100) {
        new_x = file->app.player_x + cos(file->app.angle + M_PI_2) * MOVE_STEP;
        new_y = file->app.player_y + sin(file->app.angle + M_PI_2) * MOVE_STEP;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x += cos(file->app.angle + M_PI_2) * MOVE_STEP;
            file->app.player_y += sin(file->app.angle + M_PI_2) * MOVE_STEP;
        }
    }

    // redraw the scene
    draw_frame(file);
    return (0);
}

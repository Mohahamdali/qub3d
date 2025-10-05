/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manter <manter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:16:22 by manter            #+#    #+#             */
/*   Updated: 2025/09/30 22:48:53 by manter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../qub3d.h"

// check if a position is inside a wall
static int is_wall(int x, int y, t_file *file)
{
    // (void)x;
    // (void)y;
    // (void)file;
    // // int grid_x = x / (float)TILE;
    // // int grid_y = y / (float)TILE;
    // // if (file->map[grid_y][grid_x] == '1') // 1 = wall
    // //     return (1);
    // return (0);

    if ((int)x >= 0 && (int)x < file->map_height * 64 \
	&& (int)y >= 0 && (int)y < file->map_width * 64 && \
	(file->map[(int)(x / 64)][(int)(y / 64)] != '1') && \
	(file->map[(int)((x + 10) / 64)][(int)((y + 10) / 64)] != '1')
	&& (file->map[(int)((x + 10) / 64)][(int)((y - 10) / 64)] != '1')
	&& (file->map[(int)((x - 10) / 64)][(int)((y + 10) / 64)] != '1')
	&& (file->map[(int)((x - 10) / 64)][(int)((y - 10) / 64)] != '1'))
	{
		return (false);
	}
	return (true);
}

int key_hook(int key, t_file *file)
{
    float new_x, new_y;

    if (key == 65307) // ESC
        exit(0);
    // rotate left (← arrow)
    if (key == 65361)
        file->app.angle -= ROT_STEP;
    // rotate right (→ arrow)
    if (key == 65363)
        file->app.angle += ROT_STEP;
    // forward (W)
    if (key == 119) {
        new_x = file->app.player_x + sin(file->app.angle) * SPED;
        new_y = file->app.player_y + cos(file->app.angle) * SPED;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x += SPED * sin(file->app.angle);
            file->app.player_y += SPED * cos(file->app.angle);
        }
    }
    // backward (S)
    if (key == 115) {
        new_x = file->app.player_x - sin(file->app.angle) * SPED;
        new_y = file->app.player_y - cos(file->app.angle) * SPED;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x -= SPED * sin(file->app.angle);
            file->app.player_y -= SPED * cos(file->app.angle);
        }
    }
    // strafe left (A)
    if (key == 97) {
        new_x = file->app.player_x - sin(file->app.angle + M_PI_2) * SPED;
        new_y = file->app.player_y - cos(file->app.angle + M_PI_2) * SPED;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x -= sin(file->app.angle + (M_PI / 2)) * SPED;
            file->app.player_y -= cos(file->app.angle + (M_PI / 2)) * SPED;
        }
    }
    // strafe right (D)
    if (key == 100) {
        new_x = file->app.player_x + sin(file->app.angle + M_PI_2) * SPED;
        new_y = file->app.player_y + cos(file->app.angle + M_PI_2) * SPED;
        if (!is_wall(new_x, new_y, file)) {
            file->app.player_x += sin(file->app.angle + (M_PI / 2)) * SPED;
            file->app.player_y += cos(file->app.angle + (M_PI / 2)) * SPED;
        }
    }

    // redraw the scene
    draw_frame(file);
    return (0);
}

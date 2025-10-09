/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recast_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:11:27 by manter            #+#    #+#             */
/*   Updated: 2025/10/09 15:24:13 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"


inline int ft_is_wall(int row, int col, t_file *file)
{
    if (row < 0 || row >= file->map_height || col < 0 || col >= file->map_width)
        return 1; // treat out-of-bounds as solid
    return (file->map[row][col] == '1');
}

void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0, dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps <= 0) { put_px(img, x0, y0, color); return; }
    float sx = dx / (float)steps, sy = dy / (float)steps;
    float x = (float)x0, y = (float)y0;
    for (int i = 0; i <= steps; ++i) { put_px(img, (int)(x+0.5f), (int)(y+0.5f), color); x += sx; y += sy; }
}
void put_px(t_img *img, int x, int y, int color)
{
    if (x < 0 || y < 0 || x >= img->w || y >= img->h) return;
    char *dst = img->data + (y * img->line_len + x * (img->bpp / 8));
    *(int *)dst = color;
}

void fill_rect(t_img *img, int x, int y, int w, int h, int color)
{
    for (int j = 0; j < h; ++j)
        for (int i = 0; i < w; ++i)
            put_px(img, x + i, y + j, color);
}

void draw_player(t_img *img, int px, int py, int size, int color)
{
    for (int y = -size; y <= size; y++) {
        for (int x = -size; x <= size; x++) {
            if (x*x + y*y <= size*size)  // circle formula
                put_px(img, px + x, py + y, color);
        }
    }
}

int close_hook(t_app *app)
{
    mlx_destroy_window(app->mlx, app->win);
    exit(0);
    return 0;
}
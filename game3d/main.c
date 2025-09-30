/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:38:03 by mhamdali          #+#    #+#             */
/*   Updated: 2025/09/30 15:20:56 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qub3d.h"


int main(int ac, char **av)
{
    t_file     file;
    t_garbage *gc = gc_init();
    if (!gc)
        return 1;   
    // Parse .cub (fills textures/colors/map; also sets player pos & angle)
    if (parser(&file, gc, ac, av) == -1)
        return 1;
    // MLX setup
    file.app.mlx = mlx_init();
    if (!file.app.mlx) return 1;  

    // DO NOT override spawn angle here (reference keeps the parsed angle)
    file.app.angle = 0.0f;  // ← keep this removed
    // Window size from map (clamped), keep since draw_frame uses img.w/h
    int win_w = (int)(file.map_width  * (float)TILE); // we need to set a default here no need to ues the maps size 
    int win_h = (int)(file.map_height * (float)TILE);
    if (win_w < WIN_W) win_w = WIN_W;
    if (win_h < WIN_H) win_h = WIN_H;

    file.app.win = mlx_new_window(file.app.mlx, win_w, win_h, "cub3d");
    file.img.ptr = mlx_new_image(file.app.mlx, win_w, win_h);
    file.img.data = mlx_get_data_addr(file.img.ptr, &file.img.bpp,
                                      &file.img.line_len, &file.img.endian);
    file.img.w = win_w;
    file.img.h = win_h;
    if (load_images(&file))
    {
        printf("Error: failed to load textures\n");
        cleanup_grb_cltr(gc);
        return 1;
    }
    // Hooks: input + close + continuous render
    mlx_hook(file.app.win,  2, 1L<<0, (int (*)(void))key_hook, &file);     // KeyPress
    // If you add key_release:  mlx_hook(file.app.win, 3, 1L<<1, key_release, &file);
    mlx_hook(file.app.win, 17, 0, (int (*)(void))close_hook, &file.app);   // DestroyNotify
    mlx_loop_hook(file.app.mlx, (int (*)(void *))draw_frame, &file);       // per-frame update

    mlx_loop(file.app.mlx);
    return 0;
}

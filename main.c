/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:38:03 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/09 15:25:04 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qub3d.h"


int main(int ac, char **av)
{
    t_file     file;
    t_garbage *gc = gc_init();
    if (!gc) return 1;

    if (parser(&file, gc, ac, av) == -1)
        return 1;
    file.app.mlx = mlx_init();
    if (!file.app.mlx) 
        return 1;  
    int win_w = (int)(file.map_width  * (float)TILE);
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
        printf("Error:\nfailed to load textures\n");
        cleanup_grb_cltr(gc);
        return 1;
    }
    mlx_hook(file.app.win,  2, 1L<<0, (int (*)(void))key_hook, &file); 

    mlx_hook(file.app.win, 17, 0, (int (*)(void))close_hook, &file.app);   
    mlx_loop_hook(file.app.mlx, (int (*)(void *))draw_frame, &file);    

    mlx_loop(file.app.mlx);
    return 0;
}

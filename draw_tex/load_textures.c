
#include "../qub3d.h"



#include <errno.h>



int load_single_img (void *mlx, t_img *img, char *path)
{
    errno = 0;
    img ->ptr = mlx_xpm_file_to_image(mlx, path, &img ->w, &img ->h);
    if (!img ->ptr)
    {
        printf("Error: could not load textures\n");
        return 1;
    }
    img ->data = mlx_get_data_addr (img ->ptr, &img ->bpp, &img ->line_len, &img ->endian);
    return 0;
}



int load_images (t_file *file)
{\
    if (load_single_img (file ->app.mlx, &file->frame[0], file ->textures.north_texture))
        return 1;
    if (load_single_img (file -> app.mlx, &file ->frame[1], file ->textures.south_texture))
        return 1;
    if (load_single_img (file ->app.mlx, &file->frame[2], file ->textures.east_texture))
        return 1;
    if (load_single_img (file -> app.mlx, &file ->frame[3], file ->textures.west_texture))
        return 1;
    return 0;
}

t_img  *choose_tex(t_file *file, t_algo algo)
{
    t_img *img;
    if (algo.wall_side == 0)
    {
        if(algo.x_step_sign > 0)
            img = &file ->frame[3];
        else
            img = &file ->frame[2];
    }
    else
    {
        if (algo.y_step_sign > 0)
            img = &file -> frame[0];
        else
            img = &file -> frame[1];
    }

    return img;
}

void main_draw(t_file *file, t_garbage *gc, t_app *app, int x)
{
    t_img *tex;
    if (load_images(file))
    {
        cleanup_grb_cltr(gc);
        exit(1);
    }

    tex = choose_tex(file, app->algo);

    // Calculate wall hit position
    double wall_p;
    if (app->algo.wall_side == 0)
        wall_p = app->player_y + app->algo.final_dist * app->dir_y;
    else
        wall_p = app->player_x + app->algo.final_dist * app->dir_x;
    wall_p -= floor(wall_p);

    // Column height
    int line_h = (int)(file->img.h / app->algo.final_dist);

    // Texture X coordinate
    int texx = (int)(wall_p * (double)(tex->w));
    if ((app->algo.wall_side == 0 && app->algo.x_step_sign > 0) ||
        (app->algo.wall_side == 1 && app->algo.y_step_sign > 0))
        texx = tex->w - texx - 1;
    if (texx < 0) texx = 0;
    if (texx >= tex->w) texx = tex->w - 1;

    // Texture vertical step
    double step = (double)tex->h / line_h;
    double texPos = 0.0; // start at top for each column

    int start = file->start_draw;
    int end   = file->end_draw;

    for (int y = start; y < end; y++)
    {
        int texY = (int)texPos;
        if (texY < 0) texY = 0;
        if (texY >= tex->h) texY = tex->h - 1;

        char *pixel = tex->data + texY * tex->line_len + texx * (tex->bpp / 8);
        int color = 0;

        if (tex->bpp == 32)
            color = *(int*)pixel;
        else if (tex->bpp == 24)
        {
            unsigned char *p = (unsigned char*)pixel;
            color = (p[0] << 16) | (p[1] << 8) | p[2];
        }

        put_px(&file->img, x, y, color);

        texPos += step;
    }
}



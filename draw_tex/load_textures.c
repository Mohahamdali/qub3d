
#include "../qub3d.h"


int load_single_img (void *mlx, t_img *img, char *path)
{
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
{
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

void main_draw(t_file *file, t_app *app, int x, float ray_angle)
{
    t_img *tex = choose_tex(file, app->algo);
    if (!tex)
        return;
    
    float wall_height = (float)file->img.h / app->algo.final_dist;
    

    double wall_p;
    if (app->algo.wall_side == 0)
        wall_p = app->player_y + app->algo.final_dist * sin(ray_angle);
    else
        wall_p = app->player_x + app->algo.final_dist * cos(ray_angle);
    
    wall_p -= floor(wall_p);
    
    int texx = (int)(wall_p * tex->w);
    if (texx >= tex->w) 
        texx = tex->w - 1;
    if (texx < 0)
        texx = 0;
    
    if ((app->algo.wall_side == 0 && app->algo.x_step_sign > 0) ||
        (app->algo.wall_side == 1 && app->algo.y_step_sign < 0))
        texx = tex->w - texx - 1;
    
    double step = (double)tex->h / wall_height;
    double texPos = 0;

    //notice part mohima can optimize fiha 

    // if (file->start_draw > (file->img.h / 2) - (wall_height / 2))
    // {
    //     int clipped = file->start_draw - ((file->img.h / 2) - (wall_height / 2));
    //     texPos = clipped * step;
    // }
    
    int y = file->start_draw;
    while (y < file->end_draw )
    {
        int texY = (int)texPos;
        if (texY < 0) 
            texY = 0;
        if (texY >= tex->h)
            texY = tex->h - 1;
        char *pixel = tex->data + (texY * tex->line_len + texx * (tex->bpp / 8));
        unsigned char b = pixel[0];
        unsigned char g = pixel[1];
        unsigned char r = pixel[2];
        
        int color = (r << 16) | (g << 8) | b;
        
        put_px(&file->img, x, y, color);
        
        texPos += step;
        y++;
    }
}
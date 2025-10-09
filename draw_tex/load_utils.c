/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:15:18 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/09 19:59:03 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

int	load_single_img(void *mlx, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(mlx, path, &img->w, &img->h);
	if (!img->ptr)
	{
		printf("Error: could not load textures\n");
		return (1);
	}
	img->data = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_len, &img->endian);
	return (0);
}

t_img	*choose_tex(t_file *file, t_algo algo)
{
	t_img	*img;

	if (algo.wall_side == 0)
	{
		if (algo.x_step_sign > 0)
			img = &file->frame[3];
		else
			img = &file->frame[2];
	}
	else
	{
		if (algo.y_step_sign > 0)
			img = &file->frame[0];
		else
			img = &file->frame[1];
	}
	return (img);
}

int	load_images(t_file *file)
{
	if (load_single_img(file->app.mlx, &file->frame[0],
			file->textures.north_texture))
		return (1);
	if (load_single_img(file->app.mlx, &file->frame[1],
			file->textures.south_texture))
		return (1);
	if (load_single_img(file->app.mlx, &file->frame[2],
			file->textures.east_texture))
		return (1);
	if (load_single_img(file->app.mlx, &file->frame[3],
			file->textures.west_texture))
		return (1);
	return (0);
}

static int	get_color_from_texture(t_img *tex, int texy, int texx)
{
	char			*pixel;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	int				color;

	pixel = tex->data + (texy * tex->line_len + texx * (tex->bpp / 8));
	b = pixel[0];
	g = pixel[1];
	r = pixel[2];
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	draw_wall_slice(t_file *file, t_img *tex, int texx,
			float wall_height)
{
	double	step;
	double	texpos;
	int		y;
	int		texy;
	int		color;

	step = (double)tex->h / wall_height;
	init_tex_position(file, wall_height, step, &texpos);
	y = file->start_draw;
	while (y < file->end_draw)
	{
		texy = (int)texpos;
		if (texy < 0)
			texy = 0;
		if (texy >= tex->h)
			texy = tex->h - 1;
		color = get_color_from_texture(tex, texy, texx);
		put_px(&file->img, file->x, y, color);
		texpos += step;
		y++;
	}
}

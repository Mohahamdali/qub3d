/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:31:58 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/05 16:33:06 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void	calc_wall_horizontal(t_app *app, float ray_angle, double *wall_p)
{
	double	playerx;
	double	playery;
	double	wall_x_pixel;
	double	wall_y_pixel;
	double	t;

	playerx = app->player_y;
	playery = app->player_x;
	if (app->algo.x_step_sign > 0)
		wall_x_pixel = app->algo.x_pos * TILE;
	else
		wall_x_pixel = (app->algo.x_pos + 1) * TILE;
	t = (wall_x_pixel - playerx) / cos(ray_angle);
	wall_y_pixel = playery + t * sin(ray_angle);
	*wall_p = wall_y_pixel / (double)TILE;
	*wall_p -= floor(*wall_p);
}

static void	calc_wall_vertical(t_app *app, float ray_angle, double *wall_p)
{
	double	playerx;
	double	playery;
	double	wall_y_pixel;
	double	wall_x_pixel;
	double	t;

	playerx = app->player_y;
	playery = app->player_x;
	if (app->algo.y_step_sign > 0)
		wall_y_pixel = app->algo.y_pos * TILE;
	else
		wall_y_pixel = (app->algo.y_pos + 1) * TILE;
	t = (wall_y_pixel - playery) / sin(ray_angle);
	wall_x_pixel = playerx + t * cos(ray_angle);
	*wall_p = wall_x_pixel / (double)TILE;
	*wall_p -= floor(*wall_p);
}

static int	calculate_texture_x(t_app *app, t_img *tex, double wall_p)
{
	int	texx;

	texx = (int)(wall_p * tex->w);
	if (texx >= tex->w)
		texx = tex->w - 1;
	if (texx < 0)
		texx = 0;
	if ((app->algo.wall_side == 0 && app->algo.x_step_sign > 0)
		|| (app->algo.wall_side == 1 && app->algo.y_step_sign < 0))
		texx = tex->w - texx - 1;
	return (texx);
}

void	init_tex_position(t_file *file, float wall_height, double step,
			double *texpos)
{
	int	clipped;

	*texpos = 0;
	if (file->start_draw > (file->img.h / 2) - (wall_height / 2))
	{
		clipped = file->start_draw - ((file->img.h / 2) - (wall_height / 2));
		*texpos = clipped * step;
	}
}

void	main_draw(t_file *file, t_app *app, int x, float ray_angle)
{
	t_img	*tex;
	float	wall_height;
	double	wall_p;
	int		texx;

    file -> x = x;
	tex = choose_tex(file, app->algo);
	if (!tex)
		return ;
	wall_height = (float)file->img.h / app->algo.final_dist;
	if (app->algo.wall_side == 0)
		calc_wall_horizontal(app, ray_angle, &wall_p);
	else
		calc_wall_vertical(app, ray_angle, &wall_p);
	texx = calculate_texture_x(app, tex, wall_p);
	draw_wall_slice(file, tex, texx, wall_height);
}

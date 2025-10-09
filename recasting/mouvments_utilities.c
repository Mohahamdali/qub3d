/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvments_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manter <manter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 06:39:58 by manter            #+#    #+#             */
/*   Updated: 2025/10/08 08:15:50 by manter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void	ft_move_forward(t_file *file)
{
	float	new_x;
	float	new_y;

	new_x = file->app.player_x + sin(file->app.angle) * SPED;
	new_y = file->app.player_y + cos(file->app.angle) * SPED;
	if (!ft_is_wall(new_x, new_y, file))
	{
		file->app.player_x += SPED * sin(file->app.angle);
		file->app.player_y += SPED * cos(file->app.angle);
	}
}

static void	ft_move_backward(t_file *file)
{
	float	new_x;
	float	new_y;

	new_x = file->app.player_x - sin(file->app.angle) * SPED;
	new_y = file->app.player_y - cos(file->app.angle) * SPED;
	if (!ft_is_wall(new_x, new_y, file))
	{
		file->app.player_x -= SPED * sin(file->app.angle);
		file->app.player_y -= SPED * cos(file->app.angle);
	}
}

static void	ft_move_left(t_file *file)
{
	float	new_x;
	float	new_y;

	new_x = file->app.player_x - sin(file->app.angle + M_PI_2) * SPED;
	new_y = file->app.player_y - cos(file->app.angle + M_PI_2) * SPED;
	if (!ft_is_wall(new_x, new_y, file))
	{
		file->app.player_x -= sin(file->app.angle + (PI / 2)) * SPED;
		file->app.player_y -= cos(file->app.angle + (PI / 2)) * SPED;
	}
}	

static void	ft_move_right(t_file *file)
{
	float	new_x;
	float	new_y;

	new_x = file->app.player_x + sin(file->app.angle + M_PI_2) * SPED;
	new_y = file->app.player_y + cos(file->app.angle + M_PI_2) * SPED;
	if (!ft_is_wall(new_x, new_y, file))
	{
		file->app.player_x += sin(file->app.angle + (PI / 2)) * SPED;
		file->app.player_y += cos(file->app.angle + (PI / 2)) * SPED;
	}
}

void	ft_handle_movement(int key, t_file *file)
{
	if (key == 13)
		ft_move_forward(file);
	if (key == 1)
		ft_move_backward(file);
	if (key == 0)
		ft_move_left(file);
	if (key == 2)
		ft_move_right(file);
}

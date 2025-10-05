/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:57:36 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/05 17:37:40 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void	check_duplicate(int found, t_garbage *gc)
{
	if (found > 1)
	{
		ft_putstr_fd("Error\nMore player in map\n", 2);
		cleanup_grb_cltr(gc);
		exit(1);
	}
	if (found == 0)
	{
		ft_putstr_fd("Error\nNO player in map\n", 2);
		cleanup_grb_cltr(gc);
		exit(1);
	}
}

static void	set_player_angle(char c, t_app *p)
{
	if (c == 'N')
		p->angle = 3 * M_PI_2;
	else if (c == 'S')
		p->angle = M_PI_2;
	else if (c == 'E')
		p->angle = 0;
	else if (c == 'W')
		p->angle = M_PI;
}

void	find_player_in_map(char **map, t_app *p, t_garbage *gc)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				set_player_angle(map[i][j], p);
				p->player_x = (j + 0.5f) * TILE;
				p->player_y = (i + 0.5f) * TILE;
				found++;
			}
			j++;
		}
		i++;
	}
	check_duplicate(found, gc);
}

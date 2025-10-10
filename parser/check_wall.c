/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 02:19:18 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/10 11:57:27 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static int	check_first_last_row(t_file *file)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(file->map[0]) - 1;
	while (x < len)
	{
		if (file->map[0][x] != '1' && file->map[0][x] != ' ')
			return (-1);
		x++;
	}
	x = 0;
	len = ft_strlen(file->map[file->map_height - 1]);
	while (x < len - 1)
	{
		if (file->map[file->map_height - 1][x] != '1'
			&& file->map[file->map_height - 1][x] != ' ')
			return (-1);
		x++;
	}
	return (0);
}

int	check_walls(t_file *file)
{
	int	y;
	int	len;

	if (check_first_last_row(file) == -1)
		return (-1);
	y = 1;
	while (y < file->map_height - 1)
	{
		len = ft_strlen(file->map[y]) - 1;
		if (len == 0)
			return (-1);
		if (file->map[y][0] != '1' && file->map[y][0] != ' ')
			return (-1);
		if (file->map[y][len - 1] != '1'
			&& file->map[y][len - 1] != ' ')
			return (-1);
		y++;
	}
	return (0);
}

int	is_valid_cell(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_cell(char **map, int y, int x, int map_height)
{
	int	row_len;

	if (y <= 0)
		return (-1);
	row_len = ft_strlen(map[y - 1]);
	if (x >= row_len || !is_valid_cell(map[y - 1][x]))
		return (-1);
	if (y + 1 >= map_height)
		return (-1);
	row_len = ft_strlen(map[y + 1]);
	if (x >= row_len || !is_valid_cell(map[y + 1][x]))
		return (-1);
	if (x <= 0)
		return (-1);
	if (!is_valid_cell(map[y][x - 1]))
		return (-1);
	row_len = ft_strlen(map[y]);
	if (x + 1 >= row_len || !is_valid_cell(map[y][x + 1]))
		return (-1);
	return (0);
}
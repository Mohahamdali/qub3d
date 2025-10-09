/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:35:40 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/09 14:13:08 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void	handle_textures(t_file *file, char *line, t_garbage *gc)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (file->flag.no_set)
		{
			ft_putstr_fd("Error\nDuplicate: NO\n", 2);
			cleanup_grb_cltr(gc);
			exit(1);
		}
		file->textures.north_texture = g_strdup(gc,
				trim_newline_and_spaces(line + 3));
		file->flag.no_set = 1;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (file->flag.so_set)
		{
			ft_putstr_fd("Error\nDuplicate: SO\n", 2);
			cleanup_grb_cltr(gc);
			exit(1);
		}
		file->textures.south_texture = g_strdup(gc,
				trim_newline_and_spaces(line + 3));
		file->flag.so_set = 1;
	}
}

static void	handle_west_east(t_file *file, char *line, t_garbage *gc)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (file->flag.we_set)
		{
			ft_putstr_fd("Error\nDuplicate: WE\n", 2);
			cleanup_grb_cltr(gc);
			exit(1);
		}
		file->textures.west_texture = g_strdup(gc,
				trim_newline_and_spaces(line + 3));
		file->flag.we_set = 1;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (file->flag.east_set)
		{
			ft_putstr_fd("Error\nDuplicate: EA\n", 2);
			cleanup_grb_cltr(gc);
			exit(1);
		}
		file->textures.east_texture = g_strdup(gc,
				trim_newline_and_spaces(line + 3));
		file->flag.east_set = 1;
	}
}

static void	handle_colors(t_file *file, char *line, t_garbage *gc)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (file->flag.floor_color_set)
		{
			ft_putstr_fd("Error\nDuplicate: F\n", 2);
			cleanup_grb_cltr(gc);
			exit(1);
		}
		parse_color(trim_newline_and_spaces(line + 2), file->floor_color, gc);
		file->flag.floor_color_set = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (file->flag.cealing_color_set)
		{
			ft_putstr_fd("Error\nDuplicate: C\n", 2);
			cleanup_grb_cltr(gc);
			exit(1);
		}
		parse_color(trim_newline_and_spaces(line + 2), file->cealing_color, gc);
		file->flag.cealing_color_set = 1;
	}
}

static void	process_line(t_file *file, char *line, t_garbage *gc)
{
	handle_textures(file, line, gc);
	handle_west_east(file, line, gc);
	handle_colors(file, line, gc);
	if (*line != '\n' && ft_strncmp(line, "NO ", 3) != 0
		&& ft_strncmp(line, "SO ", 3) != 0
		&& ft_strncmp(line, "WE ", 3) != 0
		&& ft_strncmp(line, "EA ", 3) != 0
		&& ft_strncmp(line, "F ", 2) != 0
		&& ft_strncmp(line, "C ", 2) != 0)
	{
		message_error("Error\nCheck if all required identifiers are present\n", \
			gc);
	}
}

void	if_all(t_file *file, char *line, int *this_is_map, t_garbage *gc)
{
	if (!*this_is_map && is_map_line(line))
	{
		*this_is_map = 1;
		if (file -> flag.floor_color_set  == 0|| file -> flag.cealing_color_set == 0)
		message_error("Error\nCheck if all required identifiers are present\n", \
			gc);
		return ;
	}
	process_line(file, line, gc);
}

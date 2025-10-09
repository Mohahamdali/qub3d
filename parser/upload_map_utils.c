/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:26:56 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/09 20:23:51 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] == ' ')
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*trim_newline_and_spaces(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' '))
		str[--len] = '\0';
	return (str);
}

int	count_map_lines(char *filename)
{
	int		fd;
	char	*line;
	int		this_is_map;
	int		map_lines;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	this_is_map = 0;
	map_lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!this_is_map)
		{
			if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
				this_is_map = 1;
		}
		if (this_is_map)
			map_lines++;
		free(line);
	}
	return (close(fd), map_lines);
}

static void	pad_map_line(t_file *file, int i, int max_len, t_garbage *gc)
{
	char	*new_line;
	int		len;
	int		has_newline;
	int		content_len;
	int		j;

	len = ft_strlen(file->map[i]);
	has_newline = (len > 0 && file->map[i][len - 1] == '\n');
	if (has_newline)
		content_len = len - 1;
	else
		content_len = len;
	if (content_len < max_len || !has_newline)
	{
		new_line = g_malloc(gc, max_len + 2);
		if (!new_line)
			message_error("empty_line\n", gc);
		ft_strlcpy(new_line, file->map[i], len + 1);
		j = content_len;
		while (j < max_len)
			new_line[j++] = ' ';
		new_line[max_len] = '\n';
		new_line[max_len + 1] = '\0';
		file->map[i] = new_line;
	}
}

void	fix_map_widths(t_file *file, t_garbage *gc)
{
	int	max_len;
	int	len;
	int	i;

	max_len = 0;
	i = 0;
	while (i < file->map_height)
	{
		len = ft_strlen(file->map[i]);
		if (len > 0 && file->map[i][len - 1] == '\n')
			len--;
		if (len > max_len)
			max_len = len;
		i++;
	}
	file->map_width = max_len;
	i = 0;
	while (i < file->map_height)
	{
		pad_map_line(file, i, max_len, gc);
		i++;
	}
}

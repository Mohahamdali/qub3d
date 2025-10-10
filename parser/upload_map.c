/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 20:09:22 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/10 12:11:16 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

void	message_error(char *str, t_garbage *gc)
{
	ft_putstr_fd(str, 2);
	cleanup_grb_cltr(gc);
	exit(1);
}

int	parse_color(char *str, int color[3], t_garbage *gc)
{
	int		i;
	char	*tmp;
	char	*token;

	i = 0;
	tmp = str;
	if (!((*tmp >= '0' && *tmp <= '9') || *tmp != '-' || *tmp != '+'))
		message_error("Error\nRGB\n", gc);
	while (i < 3)
	{
		token = tmp;
		while (*tmp && *tmp != ',')
			tmp++;
		if (*tmp == ',' && i != 2)
			*tmp++ = '\0';
		if (!token[0])
			message_error("Error\nrgb\n", gc);
		color[i++] = ft_atoi(token, gc);
		if (i == 3 && *tmp == ',')
			message_error("Error\nToo many values for RGB\n", gc);
	}
	if (*tmp != '\0')
		message_error("Error rgb\n", gc);
	return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

static int	init_file_data(t_file *file, char *name_file, t_garbage *gc)
{
	(void)gc;
	file->map_height = count_map_lines(name_file);
	if (file->map_height <= 0)
		return (-1);
	file->map = g_malloc(gc, sizeof(char *) * (file->map_height + 1));
	if (!file->map)
		return (-1);
	return (0);
}

static void	process_file_line(t_file *file, char *line,
	int *i, t_garbage *gc)
{
	static int	this_is_map = 0;

	if (!this_is_map)
		if_all(file, line, &this_is_map, gc);
	if (this_is_map)
	{
		file->map[*i] = g_strdup(gc, line);
		(*i)++;
	}
}

int	upload_file(t_file *file, char *name_file, t_garbage *gc)
{
	char	*line;
	int		fd;
	int		i;

	if (init_file_data(file, name_file, gc) == -1)
		return (-1);
	i = 0;
	fd = open(name_file, O_RDWR, 0666);
	if (fd == -1)
		return (perror("fd"), -1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_file_line(file, line, &i, gc);
		free(line);
	}
	file->map[i] = NULL;
	close(fd);
	return (0);
}

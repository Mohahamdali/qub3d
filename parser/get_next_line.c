/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:38:52 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 01:06:22 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static char *append_char(char *s, char c, t_garbage *gc)
{
	int i = 0;
	int j = 0;
	char *new_str;
	
	while (s && s[i])
		i++;
	new_str = g_malloc(gc,i + 2);
	if (!new_str)
		return (NULL);
	while (j < i)
	{
		new_str[j] = s[j];
		j++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return new_str;
}


char *get_next_line(int fd, t_garbage *gc)
{
	char	*line = NULL;
	char	ch;
	int		bytes;

	if (fd < 0)
		return (NULL);
	while ((bytes = read(fd, &ch, 1)) > 0)
	{
		line = append_char(line, ch, gc);
		if (!line)
			return (NULL);
		if (ch == '\n')
			break;
	}
	if (bytes == -1 || (bytes == 0 && !line))
		return (NULL);
	return (line);
}

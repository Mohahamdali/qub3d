/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:38:52 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/05 17:38:42 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static char	*append_char(char *s, char c)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (s && s[i])
		i++;
	new_str = malloc(i + 2);
	if (!new_str)
		return (NULL);
	while (j < i)
	{
		new_str[j] = s[j];
		j++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	if (s)
		free(s);
	return (new_str);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	ch;
	int		bytes;

	line = NULL;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		bytes = read(fd, &ch, 1);
		if (bytes <= 0)
			break ;
		line = append_char(line, ch);
		if (!line)
			return (NULL);
		if (ch == '\n')
			break ;
	}
	if (bytes == -1 || (bytes == 0 && !line))
		return (NULL);
	return (line);
}

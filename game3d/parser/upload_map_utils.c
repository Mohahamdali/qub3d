/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:26:56 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 03:00:27 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"


int is_map_line(char *line)
{
    int i = 0;
    if (line[i] == '\n')
        return 0;
    while (line[i] == ' ')
        i++;
    while (line[i] && line[i] != '\n' )
    {
        if (line[i] != '0' && line[i] != '1' &&
            line[i] != 'N' && line[i] != 'S' &&
            line[i] != 'E' && line[i] != 'W' &&
            line[i] != ' ')
            return 0;
        i++;
    }
    return 1;
}


void fix_map_widths(t_file *file, t_garbage *gc)
{
    int max_len = 0;
    int len, i = 0, j = 0;
    int has_newline = 0;
    while (i < file->map_height)
    {
        len = ft_strlen(file->map[i]);
        if (len > 0 && file->map[i][len - 1] == '\n')
            len--;
        if (len > max_len)
            max_len = len;
        i++;
    }
    file -> map_width = max_len;
    i = 0;
    char *new_line;
    int content_len;
    while (i < file->map_height)
    {
        len = ft_strlen(file->map[i]);
        has_newline = (len > 0 && file->map[i][len - 1] == '\n');
        content_len = has_newline ? len - 1 : len;
        if (content_len < max_len || !has_newline)
        {
            new_line = g_malloc(gc, max_len + 2);
            if (!new_line)
            {
                cleanup_grb_cltr(gc);
                exit(1);
            }
            ft_strlcpy(new_line, file->map[i], len + 1);
            j = content_len;
            while (j < max_len)
                new_line[j++] = ' ';
            new_line[max_len] = '\n';
            new_line[max_len + 1] = '\0';
            file->map[i] = new_line;
        }
        i++;
    }
}

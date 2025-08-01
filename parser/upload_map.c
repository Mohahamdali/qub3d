/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:29:29 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/01 01:34:57 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

void parse_color(char *str, int color[3])
{
    int i = 0;
    char *tmp;
    char *token;

    tmp = str;
    while (i < 3)
    {
        token = tmp;
        while (*tmp && *tmp != ',')
            tmp++;
        if (*tmp)
        {
            *tmp = '\0';
            tmp++;
        }
        color[i] = ft_atoi(token);
        i++;
    }
}

int count_map_lines(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;

    char *line;
    int this_is_map = 0;
    int map_lines = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (!this_is_map)
        {
            if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
                this_is_map = 1;
        }
        if (this_is_map)
            map_lines++;

        free(line);
    }
    close(fd);
    return map_lines;
}

void if_all (t_file *file, char *line, int *this_is_map)
{
    if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
        *this_is_map = 1;
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        free(file->north_texture);
        file->north_texture = ft_strdup(line + 3);
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        free(file->south_texture);
        file->south_texture = ft_strdup(line + 3);
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        free(file->west_texture);
        file->west_texture = ft_strdup(line + 3);
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        free(file->east_texture);
        file->east_texture = ft_strdup(line + 3);
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
        parse_color(line + 2, file->floor_color);
    else if (ft_strncmp(line, "C ", 2) == 0)
        parse_color(line + 2, file->cealing_color);
}

int upload_file (t_file *file, char *name_file)
{
    char *line;
    int fd;

    file ->map_height = count_map_lines(name_file);
    if (file -> map_height <= 0)
        return -1;
    file -> map = malloc (sizeof(char *) * file -> map_height);
    if (!file -> map)
        return -1;
    int this_is_map = 0;
    int i = 0;
    fd = open (name_file, O_RDWR,0666);
    if (fd == -1)
    {
        perror("fd");
        return -1;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!this_is_map)
        {
            if_all(file,line,&this_is_map);  
        }
        if (this_is_map)
            file -> map[i++] = ft_strdup(line);
    free(line);
}
file -> map[i] = NULL;
close(fd);
return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:29:29 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/01 11:35:02 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

void parse_color(char *str, int color[3], t_garbage *gc)
{
    int   i = 0;
    char *tmp;
    char *token;
    tmp = str;
    if (!(*tmp >= '0' && *tmp <= '9'))
        return (write(1,"bro RGB its numbers not characters\n",37),exit(1));
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
        color[i] = ft_atoi(token, gc);
        i++;
    }
    if (*tmp != '\0')
        return (ft_putstr_fd("ERROR\nMORE RGB\n", 2), cleanup_grb_cltr(gc), exit(1));
}

int count_map_lines(char *filename, t_garbage *gc)
{
    int   fd = open(filename, O_RDONLY);
    if (fd == -1)
        return -1;

    char *line;
    int   this_is_map = 0;
    int   map_lines = 0;

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

char *trim_newline_and_spaces(char *str)
{
    int len = ft_strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' '))
        str[--len] = '\0';
    return str;
}

void if_all(t_file *file, char *line, int *this_is_map, t_garbage *gc)
{
    if (!*this_is_map && is_map_line(line))
    {
        *this_is_map = 1;
        return;
    }
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        if (file->flag.no_set)
        {
            ft_putstr_fd("Error\nDuplicate: NO\n", 2);
            cleanup_grb_cltr(gc);
            exit(1);
        }
        file->textures.north_texture = g_strdup(gc, trim_newline_and_spaces(line + 3));
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
        file->textures.south_texture = g_strdup(gc, trim_newline_and_spaces(line + 3));
        file->flag.so_set = 1;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        if (file->flag.we_set)
        {
            ft_putstr_fd("Error\nDuplicate: WE\n", 2);
            cleanup_grb_cltr(gc);
            exit(1);
        }
        file->textures.west_texture = g_strdup(gc, trim_newline_and_spaces(line + 3));
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
        file->textures.east_texture = g_strdup(gc,trim_newline_and_spaces(line + 3));
        file->flag.east_set = 1;
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
    {
        if (file->flag.floor_color_set)
        {
            ft_putstr_fd("Error\nDuplicate: F\n", 2);
            cleanup_grb_cltr(gc);
            exit(1);
        }
        parse_color(line + 2, file->floor_color, gc);
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
        parse_color(line + 2, file->cealing_color, gc);
        file->flag.cealing_color_set = 1;
    }
    else if (*line != '\n')
    {
        ft_putstr_fd("Error\nCheck if all required identifiers are present in the file\n", 2);
        cleanup_grb_cltr(gc);
        exit(1);
    }
}

int upload_file(t_file *file, char *name_file, t_garbage *gc)
{
    char *line;
    int   fd;

    file->map_height = count_map_lines(name_file, gc);
    if (file->map_height <= 0)
        return -1;

    file->map = g_malloc(gc, sizeof(char *) * (file->map_height + 1));
    if (!file->map)
        return -1;

    int this_is_map = 0;
    int i = 0;
    fd = open(name_file, O_RDWR, 0666);
    if (fd == -1)
    {
        perror("fd");
        return -1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        if (!this_is_map)
        {
            if_all(file, line, &this_is_map, gc);
        }
        if (this_is_map)
        {
            file->map[i++] = g_strdup(gc, line);
        }
        free(line); 
    }
    file->map[i] = NULL;
    close(fd);
    return 0;
}

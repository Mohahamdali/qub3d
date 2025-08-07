/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:59:12 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 04:14:42 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../qub3d.h"

static void check_file_name (int ac ,char *av)
{
     if (ac != 2)
     {
        write(2,"error argument\n",16);
        exit(1);
     }
    int len = ft_strlen(av) ;
    if(len >= 4 && ft_strcmp(av +(len - 4),".cub") != 0)
    {
        ft_putstr_fd("Error file name not valid\n",2);
        exit(1);
    }
}

static void init_structs (t_walls_textures *textures, t_flag_dup *flag)
{
    textures->north_texture = NULL;
    textures->south_texture = NULL;
    textures->west_texture = NULL;
    textures->east_texture = NULL;
    flag ->no_set = 0;
    flag ->cealing_color_set = 0;
    flag ->so_set = 0;
    flag ->east_set = 0;
    flag ->floor_color_set = 0;
    flag ->we_set = 0;
}


int parser(t_file *file, t_garbage *gc, int ac, char **av)
{
    file->file_name = av[1];
    init_structs(&file->textures, &file->flag);
    check_file_name(ac, file->file_name);
    if (upload_file(file, file->file_name, gc) == -1)
        return (ft_putstr_fd("Error:\nInvalid file\n", 2), -1);
    if (check_walls(file) == -1)
        return (ft_putstr_fd("Error:\nMap not valid\n", 2), -1);
    fix_map_widths(file, gc);
    find_player_in_map(file -> map,&file->player, gc);
    return 0;
}
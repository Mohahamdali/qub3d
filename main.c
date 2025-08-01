/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:38:03 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/01 02:43:27 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qub3d.h"


void check_file_name (int ac ,char *av)
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


void init_struct (t_file *file,char *av)
{
    file->north_texture = NULL;
    file->south_texture = NULL;
    file->west_texture = NULL;
    file->east_texture = NULL;
    file ->file_name = av;
}

int main (int ac,char **av)
{
    t_file file;
    
    init_struct(&file,av[1]);
    check_file_name(ac, file.file_name);
    if(upload_file(&file,av[1]) == -1)
        return(ft_putstr_fd("Error:\n   invalid file\n",2), -1);
    if(check_walls(&file) == -1)
        return(ft_putstr_fd("Error:\n   map not valid\n",2), -1);
}
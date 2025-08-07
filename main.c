/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:38:03 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 04:17:35 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qub3d.h"


int main(int ac, char **av)
{
    t_file file;
    t_garbage *gc;

    gc = gc_init();
    if (!gc)
        return 1;
    if (parser(&file, gc, ac, av) == -1)
        return 1;
    return 0;
}
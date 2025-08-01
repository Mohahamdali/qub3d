/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:50:22 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/01 02:30:49 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef QUB3D_H
# define QUB3D_H

#include <libc.h>
typedef struct s_file
{
    char *north_texture;  // NO
    char *south_texture;  // SO
    char *west_texture;   // WE
    char *east_texture;   // EA
    char *file_name;
    int floor_color[3];
    int cealing_color[3];
    char **map;
    int map_height;
    int map_width;
}t_file;

//libft
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int     ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
int     ft_isalnum(int c);
int     ft_isalpha(int c);
int     ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
int     upload_file (t_file *file, char *name_file);
int     check_walls (t_file *file);
#endif
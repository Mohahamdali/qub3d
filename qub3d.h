/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:50:22 by mhamdali          #+#    #+#             */
/*   Updated: 2025/08/07 04:13:57 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef QUB3D_H
# define QUB3D_H

#include <libc.h>



typedef struct s_flag_dup
{
    int no_set;
    int so_set;
    int we_set;
    int east_set;
    int floor_color_set;
    int cealing_color_set;
}   t_flag_dup;

typedef struct s_walls_textures
{
    char *north_texture;  // NO
    char *south_texture;  // SO
    char *west_texture;   // WE
    char *east_texture;   // EA
}   t_walls_textures;

typedef struct s_player
{
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
} t_player;


typedef struct s_file
{
    char                *file_name;
    int                 floor_color[3];
    int                 cealing_color[3];
    char                **map;
    t_flag_dup          flag;
    t_walls_textures    textures; 
    t_player            player;        
    int                 map_height;
    int                 map_width;
}t_file;

typedef struct s_blk
{
	void			*ptr;
	struct s_blk	*next;
}	t_blk;

typedef struct s_garbage
{
	t_blk	*blk;
	int		count;
	int		append;
}	t_garbage;


/* Big notice dir b7ali commentair 3la functiosn dyal part dyalek  bach t3raf daghya
     fin jat function*/
// parser
int     parser(t_file *file, t_garbage *gc, int ac, char **av);
int     is_map_line(char *line);
int     upload_file (t_file *file, char *name_file, t_garbage *gc);
int     check_walls (t_file *file);
void    fix_map_widths (t_file *file, t_garbage *gc);
void find_player_in_map(char **map, t_player *p, t_garbage *gc);
//libft
char	*g_strdup(t_garbage *g_c, const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int     ft_atoi(const char *str, t_garbage *gc);
char	*ft_strjoin(char const *s1, char const *s2, t_garbage *gc);
int     ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
int     ft_isalnum(int c);
int     ft_isalpha(int c);
int     ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd, t_garbage *gc);
int     ft_isdigit(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
//garbage collector
t_garbage	*gc_init(void);
void        *g_malloc(t_garbage *g_c, size_t size);
void        cleanup_grb_cltr(t_garbage *g_c);

#endif
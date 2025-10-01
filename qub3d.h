/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:50:22 by mhamdali          #+#    #+#             */
/*   Updated: 2025/10/01 16:42:12 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <mlx.h>
#include <stdlib.h>
#include <math.h>   // at top
#include <stdbool.h>

# ifndef QUB3D_H
# define QUB3D_H
#define TILE   64
#define WIN_W  1080
#define WIN_H  1000
# define PI      3.14159265359
#define CEILING_COLOR 0x87CEEB   // sky blue
#define FLOOR_COLOR   0x4B5320   // dark olive
#define WALL_LIGHT    0xAAAAAA   // for one side
#define WALL_DARK     0x888888   // for the other side
#define MOVE_STEP 5.0f     // movement speed (pixels per key press)
#define ROT_STEP  0.1f 
#define SPED 12

static const int MAP_W = 20;
static const int MAP_H = 15;

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

typedef struct s_algo{
    int   x_pos;
    int   y_pos;
    int   x_step_sign;
    int   y_step_sign;
    int   wall_side;

    float x_ray_length;   // ← was int, must be float
    float y_ray_length;   // ← was int, must be float
    float hori_dist;      // should also be float
    float vert_dist;      // should also be float
    float final_dist;
}t_algo;

typedef struct s_app
{
    double player_x;
    double player_y;
    float  angle;
    void  *mlx;
    void  *win;
    t_algo    algo;
} t_app;

typedef struct s_img 
{
    void  *ptr;
    char  *data;
    int    bpp;
    int    line_len;
    int    endian;
    int    w;
    int    h;
} t_img;

typedef struct s_file
{
    char                *file_name;
    int                 floor_color[3];
    int                 cealing_color[3];
    char                **map;
    t_flag_dup          flag;
    t_walls_textures    textures; 
    t_app               app;
    t_img               img;
    t_img               frame[4];
    int                 start_draw;
    int                 end_draw;
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
void find_player_in_map(char **map, t_app *p, t_garbage *gc);
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
char *get_next_line(int fd);
int     ft_isdigit(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
//garbage collector
t_garbage	*gc_init(void);
void        *g_malloc(t_garbage *g_c, size_t size);
void        cleanup_grb_cltr(t_garbage *g_c);
void	g_free_one_ptr(t_garbage *g_c, void *ptr);

////// recasting fcts

void put_px(t_img *img, int x, int y, int color);
void fill_rect(t_img *img, int x, int y, int w, int h, int color);
void draw_player(t_img *img, int px, int py, int size, int color);
int close_hook(t_app *app);
void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);
int ft_is_wall(int row, int col, t_file *file);
void ft_building(t_file *file, float ray_angle, int var);
int key_hook(int key, t_file *file);
int draw_frame(t_file *file);
void main_draw(t_file *file, t_app *app, int var, float ray_ongle);
int load_images (t_file *file);
#endif
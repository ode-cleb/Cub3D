/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eewu <eewu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:17:57 by eewu              #+#    #+#             */
/*   Updated: 2024/02/20 15:58:33 by eewu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define DEFAULT 0
# define GREEN_C 0xFF00
# define WHITE_C 0xFFFFFF
# define BLACK_C 0x000000
# define BLUE_C 0x0000FF
# define RED_C 0xFF0000
# define YELLOW_C 0xFFFF00
# define BLUEGRAY_C 0xBFBFFE
# define ORANGE_C 0xFF8000
# define WRONG_ARGS 1
# define WRONG_NAME 2
# define PATH_FALSE 3
# define COLOR_FALSE 4
# define WRONG_LETTERS 5
# define LEAK_IN_WALL 6
# define DOUBLE_MAP 7
# define TEX_SIZE 8
# define TEX_OPEN 9
# define MLX_ERROR 10
# define WRONG_MAP 11
# define IS_DIRECTORY 12

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_map
{
	t_list			*map_lst;
	t_list			*map_cloned;
	t_list			*start_map_cloned;
	t_list			*start_map;
	char			dir_player;
	int				len_max;
	int				map_line;

}					t_map;

typedef struct s_ray
{
	double			posx;
	double			posy;
	double			camerax;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			raydirx;
	double			raydiry;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				x;
	int				tex_x;
	int				wall_x;
}					t_ray;

typedef struct s_lst
{
	char			*str;
	int				i;
	struct lst		*next;
	struct lst		*back;
}					t_lst;

typedef struct s_img
{
	void			*mlx_img;
	void			*img;
	int				*addr;
	int				x;
	int				y;
	int				h;
	int				w;
	int				bpp;
	int				llen;
	int				endian;
	char			*path;
}					t_img;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_cub
{
	int				fd;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				playerx;
	int				playery;
	t_rgb			*f;
	t_rgb			*c;
	t_map			*map;
}					t_cub;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	char			dir;
	int				rx;
	int				ry;
	int				sizex;
	int				sizey;
	int				ceiling;
	int				floor;
	int				wall_c;
	double			wlx;
	double			texpos;
	int				up;
	int				down;
	int				rotate_r;
	int				rotate_l;
	int				right;
	int				left;
	int				free;
	int				**tex_color;
	int				**tex_buf;
	double			moovespeed;
	t_img			wall[4];
	t_img			img;
	t_ray			ray;
	t_cub			cub;
}					t_vars;

// ***********************************Display******************************** //
void				img_pix_put(t_img *img, int x, int y, int color);
void				ft_walls(t_vars *vars);
int					ft_background(t_vars *vars);
int					ft_texture(t_vars *vars, int i, int x, int y);
int					ft_display(t_vars *vars);
void				ft_put_in_buff(t_vars *vars, int y);
// *********************************Check_File******************************* //
void				print_error_msg(int key, t_cub *cub);
void				check_name(char **argv, t_cub *cub);
void				check_arg(int argc, t_cub *cub);
void				check_file(int argc, char **argv, t_cub *cub);
void				initialize(t_cub *cub);
// *********************************Check_Must******************************* //
char				*get_next_line_map(int fd);
t_list				*cpy_lst(t_list *lst);
void				check_must(char *str, t_cub *cub);
void				check_directory(char **argv, t_cub *cub);
// *******************************Check_Texture****************************** //
void				my_open(char *str, t_cub *cub);
bool				check_for_dir(char *str, char *dir, t_cub *cub);
bool				check_for_textures(char *str, t_cub *cub);

bool				check_for_color(char *str, t_cub *cub, int n);
void				check_for_map(char *str, t_cub *cub);
void				check_map(t_cub *cub);
void				check_walls(t_cub *cub);
void				ft_backtracking(t_cub *cub);
void				initialize_f_c(t_cub *cub, char c);
void				free_check_format_rgb(char *rgb, char *str, t_cub *cub);
void				free_map(t_list *lst);
void				free_cub(t_cub *cub);
// ************************************Cub3D********************************* //
void				ft_mlx_start(t_vars *vars);

// ************************************Init********************************** //
unsigned long		ft_convert_rgb(int r, int g, int b);
void				ft_init_texture(t_vars *vars, t_cub *cub);
void				ft_keyinit(t_vars *vars);
// void				ft_init(t_cub *cub, int ac, char **av);
void				ft_init_mlx(t_vars *vars, t_cub *cub);
// ************************************Free********************************** //
void				ft_free_split(char **split);
void				ft_free_exit(int i, t_vars *vars);
void				ft_free_mlx(int i, t_vars *vars);
void				ft_free_tex_color(t_vars *vars, int **tex_color, int j);
void				ft_free_buf(t_vars *vars, int **buf, int j);

// ***********************************Errors********************************* //

// ************************************STR*********************************** //
char				*ft_strdup(char *s);
char				*get_next_line(int fd);
char				*ft_gnljoin(char *stash, char *buf, int backsn_index,
						int size);
// ***********************************Utils1********************************* //
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
int					ft_backsn(char *buf);
char				*ft_strnjoin(char *s1, char *s2, size_t size);
// ***********************************Utils2********************************* //
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
void				*ft_memset(void *s, int c, size_t n);
int					ft_atoi(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
// ***********************************Split********************************** //
char				*ft_strlcat(char *dst, const char *src, int size);
char				*ft_strcpy(char *dest, const char *src);
char				**ft_tab(int nb_word, char *s, char c, char **split);
char				**ft_split(char *s, char c);
char				*ft_join(char *s1, char const *s2);
// ************************************LST*********************************** //
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
int					get_current_node_index(t_list *head, t_list *current);
// *********************************Keypress********************************* //
int					ft_keycode(int keycode, t_vars *vars);
int					ft_keycode_r(int keycode, t_vars *vars);
void				ft_dir_rightleft(t_vars *vars);
void				ft_dir_updown(t_vars *vars);
void				ft_rotate(t_vars *vars);
// *******************************Raycast_init******************************* //
double				ft_dir(char dir, int n, int x);
void				ft_rayinit(t_vars *vars);
void				ft_ray_loopinit(t_vars *vars);
// ********************************Raycasting******************************** //
void				ft_raycasting(t_vars *vars);
void				ft_perpwalldist(t_vars *vars);
int					ft_curr_map_square(t_vars *vars, int x, int y);
void				ft_perpwalldist(t_vars *vars);
// *********************************Minimap********************************** //
void				ft_minimap(t_vars *vars);
t_list				*get_previous(t_list *list, t_list *current);

#endif
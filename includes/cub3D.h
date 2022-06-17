/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:57:08 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 23:07:39 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
// #include <mlx.h>
#include "../minilibx_opengl_20191021/mlx.h"

#include "libft.h"
#include "raycast.h"
#include "texture.h"
#include "sprite.h"
#include "key.h"

#define	PI 3.141592
#define DEG	0.017453

#define	BLOCKSIZE 18
#define MINI_X 20
#define MINI_Y 20
#define MINI_SQUARE 50
#define MINI_W 250
#define MINI_H 250
#define	SCREEN_X 920
#define SCREEN_Y 600

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

typedef struct s_list {
	t_point			pos;
	float			dist;
	struct s_list	*next;
}	t_list;

typedef struct s_draw {
	char	**nswe;
	int		col_floor;
	int		col_ceil;
}	t_draw;

typedef struct s_map {
	int		width;
	int		height;
	bool	**map_move;
	char	**map_wall;
	t_point	pos;
	t_point *doors;
	int		doors_nb;
	t_point pixel_pos;
	float	theta;
}	t_map;

typedef struct s_gui {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
} 	t_gui;

typedef struct s_hook {
	bool	re;
	//*bonus
	unsigned int	minimap_on;
	unsigned int	minimap_size;
	int		x_prev;
	int		m_turn;
	int		m_dir;
	int		m_sensibility;
	bool	m_re;
	int			key_flag;
}	t_hook;

typedef struct	s_raycast {
	t_point	wall;
	float	dist;
	int		side[2];
	t_list	*door;
	t_list	*sprite;
	int		height;
}	t_raycast;

typedef struct s_sprite {
	void	*img;
	char	*addr;
	void	*mlx;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	struct s_sprite *next;
}	t_sprite;

typedef struct s_game 
{
	void	*mlx;
	void	*win;
	t_map		map;
	t_gui		gui;
	t_gui		minimap;
	t_hook		hook;
	t_draw		draw;
	t_raycast	ray;
	t_sprite	*spr;
	int			height;
	t_texture	texture;
	t_raycast	tes;
	int			pos[2];
	int			lock;
	int			sprite;
	int 		count;
	int			side;
}	t_game;

typedef struct s_tex_info {
	int		x;
	int		y;
	float	tex_pos;
	float	fract;
	float	step;
	t_img	img;
}	t_tex_info;

int	cub3D(t_game game);

/* parse */
t_game	parse(char *filename);
t_map	get_map(char **lines);
t_draw	get_draw(char **lines);

/* parse_utils */
char	**get_lines(int fd);
int		get_fd(char *filename);
int		ft_tablen(char **map);

/* parse_error */
int		check_filename(char *file);
int		verif_texture(char *dir);
int		is_surrounded(char **lines);

/* utils */
void	end_program(char *str, int tag);

/* key */
int	key_pressed(int key, t_game *game);
int	key_released(int key, t_game *game);
void	movement(t_game *game);
void	translate(t_map *map, float theta);


void	my_mlx_pixel_put(t_gui *gui, int x, int y, int color);
// int     mlx_mouse_move(mlx_win_list_t *win, int x, int y);
void	draw_cub3D(t_game *game);

int		key_hook(int key, t_game *game);

int		terminate(t_game *game);
// t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game);
t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game);
/*parse utils*/
int		check_filename(char *file);
int		check_fileformat(char *mapstr, char **map, int map_width, int map_height);

//*bonus

void	draw_minimap(t_game *game);
void	minimap_pixel_put(t_gui *gui, int x, int y, int color);
int		mouse_hook(int x, int y, t_hook *hook);
void	turn(t_map *map, int dir);
/*draw*/
void	paint_background(t_game *game);

void	draw_text(t_game *game, t_raycast ray, int ray_n, float angle);

float	perpendicular_dist(t_point from, t_point to, float angle);
//void	draw_text(t_game *game, t_img img, int h, t_raycast ray, int ray_n);

bool	is_door(t_point *door, int x, int y, int nb);
void	open_door(t_game *game);
void	draw_img(t_game *game, t_raycast *ray, int ray_x, float angle);
/* error */
t_texture	get_texture_img(t_draw draw, void *mlx_ptr);

/* utils */

float	get_angle(float old, float change);


t_door	*ft_lstnew(t_point pos, float dist);
void	ft_lstadd_front(t_door **alst, t_door *new);
void	ft_lstadd_back(t_door **alst, t_door *new);
void	free_lst(t_door *lst);
void	free_chartab(char **tab);

#endif

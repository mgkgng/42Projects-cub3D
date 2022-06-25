/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/25 15:24:06 by mlecherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall(t_game *game, t_ray ray, int ray_n, float angle)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info		info;
	int				i;

	h = get_height(ray.dist, game);
	if (game->height > 600)
		h = h / ray.dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(ray.wall, h, start);
	info.img = which_texture(ray.wall_side, &game->texture, angle);
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		put_pixel(&game->screen, ray_n, start + i, color);
	}
}

static void	draw_object(t_game *game, t_list *obj, int ray_n)
{
	int				start;
	int				h;
	unsigned int	color;
	t_tex_info		info;
	int				i;

	h = get_height(obj->dist, game);
	if (game->height > 600)
		h = h / obj->dist;
	start = 0;
	if (h < SCREEN_Y)
		start = (SCREEN_Y - h) / 2;
	info = get_tex_info(obj->pos, h, start);
	if (obj->type == DOOR && game->map.map_move[(int) obj->map_pos.y][(int) obj->map_pos.x] == false)
		info.img = game->texture.door_c;
	else if (obj->type == DOOR && game->map.map_move[(int) obj->map_pos.y][(int) obj->map_pos.x] == true)
		info.img = game->texture.door_o;
	else
		info.img = game->texture.sprite;
	i = -1;
	while (++i < h && i < SCREEN_Y)
	{
		info.y = (int) info.tex_pos & (64 - 1);
		info.tex_pos += info.step;
		color = get_data_color(info.x, info.y, info.img.addr, info.img);
		put_pixel(&game->screen, ray_n, start + i, color);
	}
}

/*		TEST DRAW SPRITE		*/
/*
static void	sprite(t_game *game, t_list *obj, int ray_x) // Il dessine le sprite d'un coup pas rayon par rayon
{
	int	numsprites;
	numsprites = ft_lstsize(obj);
	for (int i = 0; i < numsprites; i++;)
	{
		double	sprite_x = obj->pos.x - game->map.pos.x;
		double	sprite_y = obj->pos.y - game->map.pos.y;

			MATRICE	
		double	invdet;
		invdet = 1.0 / (game->lod->plane_x * game->lod->dir_y - game->lod->dir_x * game->lod->plane_y);

		double transform_x;
		transform_x = invdet * (game->lod->dir_y * sprite_x - game->lod->dir_x * sprite_y);
		double transform_y;
		transform_y = invdet * (-game->lod->plane_y * sprite_x + game->lod->plane_x * sprite_y);

		int	sprite_screen_x;
		sprite_screen_x = (int)((ray_x / 2) * (1 + transform_x / transform_y));
		int	sprite_height;
		int h; // Je sais pas si c'est h la hauteur du sprite ou h la hauteur de l'ecran.
		h = get_height(obj->dist, game);
		sprite_height = abs((int)(h / transform_y));

		// calculate lowest and highest pixel to fill in current stripe
		int	draw_start_y;
		draw_start_y = -sprite_height / 2 + h / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int	draw_end_y;
		draw_end_y = sprite_height / 2 + h / 2;
		if (draw_end_y >= SCREEN_Y)
			draw_end_y = SCREEN_Y - 1;
		
		//calculate width of the sprite
		int	spritewidth;
		spritewidth = abs((int)(h / transform_y));
		int draw_start_x;
		draw_start_x = -spritewidth / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int	draw_end_x;
		draw_end_x = spritewidth / 2 + sprite_screen_x;
		if (draw_end_x >= SCREEN_X)
			draw_end_x = SCREEN_X - 1;
		// Boucle pour dessiner
	}
}
*/

static void	draw_ray(t_game *game, t_ray *ray, int ray_x, float angle)
{
	t_list	*current_obj;

	draw_wall(game, *ray, ray_x, angle);
	current_obj = ray->object;
	while (current_obj)
	{
		draw_object(game, current_obj, ray_x);
		current_obj = current_obj->next;
	}
	free_list(ray->object);
}

static void	draw_by_ray(t_game *game)
{
	float	start_angle;
	float	angle;
	int		ray_n;
	t_ray	ray;

	start_angle = game->map.theta - ANGLE / 2;
	ray_n = -1;
	while (++ray_n < SCREEN_X)
	{
		angle = start_angle + (ray_n + 1) * ANGLE / SCREEN_X;
		game->lod->camera_x = ray_n / (double) 920;
		if (angle < 0)
			angle += M_PI * 2;
		if (angle > M_PI * 2)
			angle -= M_PI * 2;
		ray = digital_differential_analyzer(&game->map, angle);
		draw_ray(game, &ray, ray_n, angle);
	}
	// DRAW SPRITE
	t_list *tmp;
	tmp = game->map.spr;
	while (tmp)
	{
		printf("%f...%f\n", tmp->pos.x, tmp->pos.y);
		tmp = tmp->next;
	}
}

int	draw(t_game *game)
{
	move(game);
	if (game->hook.re)
	{
		paint_background(game);
		draw_by_ray(game);
		mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
		if (game->hook.minimap_on % 2)
			draw_minimap(game);
		game->hook.re = false;
	}
	return (0);
}

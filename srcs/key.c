/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/04 21:53:56 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_angle(double old, double change)
{
	double	res;
	res = old + change;
	if (res > M_PI * 2)
		return (res - M_PI * 2);
	else if (res < 0)
		return (res + M_PI * 2);
	return (res);
}

//void	translate(t_map *map, double theta)
void	translate(t_game *game)
{
	double	theta;
	if (game->hook.move_re == W)
		theta = game->map.theta;
	else if (game->hook.move_re == A)
		theta = game->map.theta - M_PI / 2;
	else if (game->hook.move_re == S)
		theta = game->map.theta + M_PI;
	else
		theta = game->map.theta + M_PI / 2;
	//* this is wall collision
	/*if (map->map2d[(int) (map->pos.x + cos(theta) * 0.1)][(int) (map->pos.y + sin(theta) * 0.1)] == false)
		return ;*/
	//printf("%f...move\n", theta);
	game->map.pos.x += cos(theta) * 0.01;
	game->map.pos.y += sin(theta) * 0.01;
}

void	turn(t_map *map, int dir)
{
	map->theta += dir * (M_PI_4 / 18);
	if (map->theta > M_PI * 2)
		map->theta -= M_PI * 2;
	if (map->theta < 0)
		map->theta += M_PI * 2;
}

int	key_hook(int key, t_game *game)
{
	//printf("%d--\n", key);
	if (key == ESC)
		terminate(game);
	if (key == UP)
	{
		//translate(&game->map, game->map.theta);
		game->hook.move_re = W;
	}
	else if (key == DOWN)
	{
		//translate(&game->map, game->map.theta + M_PI);
		game->hook.move_re = S;
	}
	else if (key == LEFT) 
	{
		//translate(&game->map, game->map.theta - M_PI / 2);
		game->hook.move_re = A;
	}
	else if (key == RIGHT)
	{
		//translate(&game->map, game->map.theta + M_PI / 2);
		game->hook.move_re = D;
	}
	else if (key == TURN_L)
		turn(&game->map, -1);
	else if (key == TURN_R)
		turn(&game->map, 1);
	//* bonus
	else if (key == MINIMAP)
		game->hook.minimap_on++;
	game->hook.re = true;
	return (0);
}
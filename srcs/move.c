/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 01:46:41 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/18 19:38:24 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	translate(t_map *map, float theta)
{
	float	new_x;
	float	new_y;

	new_x = map->pos.x + cos(theta) * 0.1;
	new_y = map->pos.y + sin(theta) * 0.1;
	if (new_x < 0 || new_x > map->width || new_y < 0 || new_y > map->height
		|| !map->map_move[(int) new_y][(int) new_x])
		return ;
	map->pos.x = new_x;
	map->pos.y = new_y;
}

void	turn(t_map *map, int dir)
{
	map->theta += dir * (M_PI_4 / 18);
	if (map->theta > M_PI * 2)
		map->theta -= M_PI * 2;
	if (map->theta < 0)
		map->theta += M_PI * 2;
}

void	move(t_game *game)
{
	if ((game->hook.key_flag & UP) > 0)
		translate(&game->map, game->map.theta);
	if ((game->hook.key_flag & LEFT) > 0)
		translate(&game->map, game->map.theta - M_PI / 2);
	if ((game->hook.key_flag & DOWN) > 0)
		translate(&game->map, game->map.theta + M_PI);
	if ((game->hook.key_flag & RIGHT) > 0)
		translate(&game->map, game->map.theta + M_PI / 2);
	if ((game->hook.key_flag & TURN_L) > 0)
		turn(&game->map, -1);
	if ((game->hook.key_flag & TURN_R) > 0)
		turn(&game->map, 1);
	game->hook.re = true;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 23:34:26 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:36:40 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

t_dda	init_dda(float theta, int xy)
{
	t_dda	res;

	if (!xy)
	{
		res.incre = 1;
		res.side = 0;
		if (theta > PI && theta < PI * 2)
		{
			res.incre = -1;
			res.side--;
		}
		res.delta = 1 / tan(theta) * res.incre;
		return (res);
	}
	res.incre = 1;
	res.side = 0;
	if (theta > PI / 2 && theta < PI / 2 * 3)
	{
		res.side--;
		res.incre = -1;
	}
	res.delta = tan(theta) * res.incre;
	return (res);
}

bool	is_through(t_map *map, int x, int y)
{
	if (x >= 0 && x < map->width
		&& y >= 0 && y < map->height
		&& (map->map_move[y][x] || map->map_wall[y][x] == 'Z'))
		return (true);
	return (false);
}

void	is_object(t_ray *ray, t_map *map, int *pos)
{
	t_point	map_pos;

	if (map->map_wall[pos[0]][pos[1]] != 'D')
		return ;
	map_pos.x = pos[1];
	map_pos.y = pos[0];
	ft_lstadd_front(&ray->object, ft_lstnew(ray->wall,
			perpendicular_dist(map->pos, ray->wall,
				map->theta + PI / 2), map_pos));
}

float	perpendicular_dist(t_point from, t_point to, float angle)
{
	float	sin_v;
	float	cos_v;

	sin_v = sin(angle);
	cos_v = cos(angle);
	return (fabs(sin_v * (to.x - from.x) - cos_v * (to.y - from.y))
		/ sqrt(pow(sin_v, 2) + pow(cos_v, 2)));
}

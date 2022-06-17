/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/17 23:14:46 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_through(t_map map, int x, int y)
{
	if (x >= 0 && x < map.width
		&& y >= 0 && y < map.height &&  
			map.map_wall[y][x] != '1')
		return (true);
	return (false);
}

void	is_object(t_raycast *ray, int c, t_map *map)
{
	if (c == 'D')
		ft_lstadd_front(&ray->door, ft_lstnew(ray->wall, 
			perpendicular_dist(map->pos, ray->wall, map->theta + PI / 2)));
	else if (c == 'Z')
		ft_lstadd_front(&ray->sprite, ft_lstnew(ray->wall, 
			perpendicular_dist(map->pos, res->wall, map->theta + PI / 2)));

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

static t_raycast	get_distX(t_map *map, t_point pos, int *where, float theta)
{
	t_raycast	res;
	float		deltaX;
	float		increY;
	int			side;

	res.door = NULL;
	res.dist = INT32_MAX;
	if (!theta || theta == PI)
		return (res);
	increY = 1;
	side = 0;
	if (theta > 0 && theta < PI)
		where[1]++;
	else
	{
		increY = -1;
		side--;
	}
	deltaX = 1 / tan(theta) * increY;
	res.wall.x = pos.x + (where[1] - pos.y) / tan(theta);
	res.wall.y = where[1];
	while (is_through(map, res.wall.x, res.wall.y + side))
	{
		is_object(&res, map[(int) res.wall.y + side][(int) res.wall.x], map);
		res.wall.x += deltaX;
		res.wall.y += increY;

	}
	res.dist = perpendicular_dist(pos, res.wall, map.theta + PI / 2);
	res.side[1] = side;
	res.side[0] = 0;
	return (res);
}

static t_raycast	get_distY(t_map *map, t_point pos, int *where, float theta)
{
	t_raycast	res;
	float		deltaY;
	float		increX;
	int			side;
	
	res.door = NULL;
	res.dist = INT32_MAX;
	if (theta == PI / 2 || theta == PI / 2 * 3)
		return (res);
	increX = 1;
	side = 0;
	if (theta > PI / 2 && theta < PI / 2 * 3)
	{
		side--;
		increX = -1;
	}
	else
		where[0]++;
	deltaY = tan(theta) * increX;
	res.wall.x = where[0];
	res.wall.y = pos.y + (where[0] - pos.x) * tan(theta);
	while (is_through(map, res.wall.x + side, res.wall.y))
	{
		is_object(&res, map[(int) res.wall.y][(int) res.wall.x + side], map);
		res.wall.x += increX;
		res.wall.y += deltaY;
	}
	res.dist = perpendicular_dist(pos, res.wall, map.theta + PI / 2);
	res.side[0] = side;
	res.side[1] = 0;
	return (res);
}





t_raycast	digital_differential_analyzer(t_map map, float theta, t_game *game)
{
	t_raycast	res_x;
	t_raycast	res_y;

	res_x = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	res_y = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (res_x.dist < res_y.dist)
	{
		game->side = 0;
		get_list(res_x.dist, &res_x.door, res_y.door);
		free_lst(res_y.door);
		return (res_x);
	}
	game->side = 1;
	get_list(res_y.dist, &res_y.door, res_x.door);
	free_lst(res_x.door);
	return (res_y);
}

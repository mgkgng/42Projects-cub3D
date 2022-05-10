/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/05/10 19:41:17 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	perpendicular_dist(double *from, double *to, double angle)
{
	double	sin_v;
	double	cos_v;

	sin_v = sin(angle);
	cos_v = cos(angle);
	return (fabs(sin_v * (to[0] - from[0]) - cos_v * (to[1] - from[1]))
		/ sqrt(pow(sin_v, 2) + pow(cos_v, 2)));
}

static t_raycast	get_distX(t_map map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaX;
	double		increY;
	int			side;

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
	while (res.wall.x >= 0 && res.wall.x < map.width
		&& map.map2d[(int) res.wall.y + side][(int) res.wall.x])
	{
		res.wall.x += deltaX;
		res.wall.y += increY;
	}
	res.dist = perpendicular_dist((double [2]) {pos.x, pos.y}, (double [2]) {res.wall.x, res.wall.y}, map.theta + PI / 2);
	return (res);
}

static t_raycast	get_distY(t_map map, t_point pos, int *where, double theta)
{
	t_raycast	res;
	double		deltaY;
	double		increX;
	int			side;

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
	while (res.wall.y >= 0 && res.wall.y < map.height
		&& map.map2d[(int) res.wall.y][(int) res.wall.x + side])
	{
		res.wall.x += increX;
		res.wall.y += deltaY;
	}
	res.dist = perpendicular_dist((double [2]) {pos.x, pos.y}, (double [2]) {res.wall.x, res.wall.y}, map.theta + PI / 2);
	return (res);
}

t_raycast	digital_differential_analyzer(t_map map, double theta)
{
	t_raycast	res_x;
	t_raycast	res_y;

	res_x = get_distX(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	res_y = get_distY(map, map.pos, (int [2]) {(int) map.pos.x, (int) map.pos.y}, theta);
	if (res_x.dist < res_y.dist)
		return (res_x);
	return (res_y);
}
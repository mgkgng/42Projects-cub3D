/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:55:35 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/14 11:56:12 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_raycast	get_distX(bool **map, t_point pos, int *case, double theta)
{
	t_raycast	res;
	double		deltaX;
	double		deltaH;
	double		increY;

	res.dist = 0;
	if (!theta || theta == M_PI)
		return (res);
	deltaH = 1 / sin(theta);
	increY = 1;
	if (theta > 0 && theta < M_PI)
	{
		pos.y += 1;
		res.wall.y = case[1] + 1;
	}
	else if (theta > M_PI && theta < M_PI * 2)
	{
		increY = -1;
		res.wall.y = case[1];
	}
	deltaX = 1 / tan(theta) * increY;
	res.dist = (case[1] - pos.y) / sin(theta);
	res.wall.x = pos.x + (case[1] - pos.y) / tan(theta);
	while (map[(int) res.wall.x][(int) res.wall.y] == true)
	{
		res.dist += deltaH;
		res.wall.x += deltaX;
		res.wall.y += increY;
	}
	return (res);
}

static t_raycast	get_distY(bool **map, t_point pos, int *case, double theta)
{
	t_raycast	res;
	double		deltaY;
	double		deltaH;
	double		increX;

	res.dist = 0;
	if (theta == M_PI_2 || theta == M_PI_2 * 3)
		return (res);
	deltaY = tan(theta);
	deltaH = 1 / cos(theta);
	increX = 1;
	if (theta > M_PI_2 && theta < M_PI_2 * 3)
		increX *= -1;
	res.dist = (pos.x - case[0]) / cos(theta) * increX;
	res.wall.x = case[0] + increX;
	res.wall.y = case[1] + (tan(theta) * (a.pos + 1 - pos.x)) * increX;
	while (map[(int) res.wall.x][(int) res.wall.y] == true)
	{
		res.dist += deltaH;
		res.wall.x += increX;
		res.wall.y += deltaY * increX;
	}
	return (res);
}

t_raycast	digital_differential_analyzer(t_point pos, char **map, double theta)
{
	t_raycast	resX;
	t_raycast	resY;

	resX = get_distX(map, pos, (int [2]) {(int) pos.x, (int) pos.y}, theta);
	resY = get_distY(map, pos, (int [2]) {(int) pos.x, (int) pos.y}, theta);
	if (resX.dist && resX.dist > resY.dist)
		return (resX);
	return (resY);
}
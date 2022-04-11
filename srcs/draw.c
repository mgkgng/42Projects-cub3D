/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:32:18 by min-kang          #+#    #+#             */
/*   Updated: 2022/04/11 18:39:38 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1. need to implement dda
// 2. need to implement raycast
// 3. need to implement the function giving the height regard of the distance between the character's point and the wall

// dda is going to return the distance

// ** should only consider the fact that north and the south (y-axis) is inverted.
// ** should also consider that fact the slope of the peripendular line of y-axis will be given as inf through atan.

double	get_distX(bool **map, t_point pos, double theta)
{
	double	h;
	double	dist;
	double	dist_offset;
	int		start;
	int		incre;
	
	h = pos.y - (int) pos.y;
	if (theta > 0 && theta < M_PI_2)
	{
		dist = h / sin(theta);
		dist_offset = 1 / sin(theta);
		start = (int) pos.y + 1;
		incre = 1;
	}
	else if (theta > M_PI_2 && theta < M_PI)
	{
		dist = (1 - h) / sin(M_PI - theta);
		dist_offset = 1 / sin(M_PI - theta);
		start = (int) pos.y;
		incre = -1;
	}
	else
		return (-1);
	while (map[][])
	{}
}

double	get_distY(t_point pos, double theta)
{
	double	w;

	w = pos.x - (int) pos.x;
	if ((theta < M_PI_4) || theta > M_PI_4 * 3)
		return (w / cos(theta));
	else if (theta > M_PI_4 && theta < M_PI_4)
		return ((1 - w) / cos(M_PI_2 - theta));
	// maybe should care about negative values
	else
		return (-1);
}

int	digital_differential_analyzer(t_point pos, t_point dir, char **map, int theta)
{
	double	distX;
	double	distY;
	double	dist;

	distX = get_distX(pos, theta);
	distY = get_distY(pos, theta);
	if (distX > distY && distX >= 0)
		dist = distX;
	else
		dist = distY;


}

void	raycast(t_point pos, char **map, int theta)
{
	// ça c'est une idee geniale ;)
	t_point	dir;
	double	dist;

	dir.x = pos.x + cos(theta);
	dir.y = pos.y + sin(theta);
	dist = digital_differential_analyzer(pos, dir, map, theta);
	// need height/distance calculator here
}

int draw(t_map map, t_raycast rc)
{
	int	i;

	i = -1;
	while (++i < ANGLE / 2)
	{
		// left
		raycast(map.pos, map.map2d, map.theta - i);
		// right 
		raycast(map.pos, map.map2d, map.theta + i);
	}
}
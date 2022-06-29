/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:49:05 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/29 23:24:04 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <pthread.h>

typedef struct s_camera
{
	float	plane_x;
	float	plane_y;
	float	dir_x;
	float	dir_y;
}	t_camera;

typedef struct s_sprite {
	float	x;
	float	y;
	float	c;
	float	x_trans;
	float	y_trans;
	float	x_screen;
	float	w;
	float	h;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
}	t_sprite;

#endif
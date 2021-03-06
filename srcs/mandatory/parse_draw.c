/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 23:04:09 by min-kang          #+#    #+#             */
/*   Updated: 2022/07/01 18:17:05 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_m.h"

static void	check_color(char *colstr)
{
	int	i;
	int	comma;

	if (colstr[0] == ',')
		end_program("Wrong RGB format", 0);
	i = -1;
	comma = 0;
	while (colstr[++i])
	{
		if (colstr[i] == ',')
		{
			comma++;
			if (comma > 2 || colstr[i + 1] == ',')
				end_program("Wrong RGB format", 0);
		}
		if (!ft_isdigit(colstr[i]) && colstr[i] != ',')
			end_program("RGB value must be numeric (without - or +)", 0);
	}
	if (comma != 2)
		end_program("Wrong RGB format", 0);
}

static int	get_color(char *colstr)
{
	int		col;
	char	**rgb;
	int		i;

	check_color(colstr);
	rgb = ft_split(colstr, ',');
	i = -1;
	while (rgb[++i])
		if (ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
			end_program("RGB value must be between 0 and 255", 0);
	col = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | (ft_atoi(rgb[2]));
	free_chartab(rgb);
	return (col);
}

static char	**get_texture(char **file)
{
	int		i;
	char	**res;

	res = malloc(sizeof(char *) * 5);
	i = -1;
	while (++i < 4)
		if (i != check_texture(file[i]) - 1)
			end_program("Wrong format for texture information.", 0);
	i = -1;
	while (++i < 4)
	{
		get_fd(file[i] + 3);
		res[i] = ft_strdup(file[i] + 3);
		if (open(res[i], O_RDWR) == -1)
			end_program(res[i], 1);
	}
	res[i] = NULL;
	return (res);
}

t_draw	get_draw(char **lines)
{
	t_draw	draw;

	draw.nswe = get_texture(lines);
	if (ft_strncmp("F ", lines[4], 2) || ft_strncmp("C ", lines[5], 2))
		end_program("Wrong format for color information.", 0);
	draw.col_floor = get_color(lines[4] + 2);
	draw.col_ceil = get_color(lines[5] + 2);
	return (draw);
}

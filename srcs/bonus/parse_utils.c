/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-kang <minguk.gaang@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:03:47 by min-kang          #+#    #+#             */
/*   Updated: 2022/06/30 22:53:56 by min-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_b.h"

char	**get_lines(int fd)
{
	char	*line;
	char	*r;
	char	**res;

	r = NULL;
	line = get_next_line(fd);
	while (line)
	{
		check_lines(line);
		r = ft_strcat(r, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	res = ft_split(r, '\n');
	free(r);
	return (res);
}

int	get_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		end_program(filename, 1);
	}
	return (fd);
}

int	ft_tablen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

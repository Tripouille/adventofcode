/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day10_part1_jm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 11:27:17 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/24 13:50:01 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

int		get_next_line(int fd, char **line);

char	*map[100];
int		map_w;
int		map_h;

int		already_view(double t, double *tan)
{
	while (*tan)
		if (*tan++ == t)
			return (1);
	return (0);
}

/*
** Count asteroid above the y position.
*/

int		count_up(int y, int x)
{
	double	tan[500] = {0};
	double	t;
	int		i;
	int		checked_y;
	int		checked_x;

	i = 0;
	checked_y = -1;
	while (++checked_y < y)
	{
		checked_x = -1;
		while (++checked_x < map_w)
		{
			t = ((double)y - checked_y) / ((double)x - checked_x);
			if (map[checked_y][checked_x] == '#' && !already_view(t, tan))
				tan[i++] = t;
		}
	}
	return (i);
}

/*
** Count asteroid below the y position.
*/

int		count_down(int y, int x)
{
	double	tan[500] = {0};
	double	t;
	int		i;
	int		checked_y;
	int		checked_x;

	i = 0;
	checked_y = y;
	while (++checked_y < map_h)
	{
		checked_x = -1;
		while (++checked_x < map_w)
		{
			t = ((double)y - checked_y) / ((double)x - checked_x);
			if (map[checked_y][checked_x] == '#' && !already_view(t, tan))
				tan[i++] = t;
		}
	}
	return (i);
}

int		count_views(char **map, int y, int x)
{
	int		views;
	int		i;

	views = count_up(y, x);
	views += count_down(y, x);
	i = -1;
	while (++i < x && map[y][i] != '#'); // check if asteroid on the left of the x position on actual y
	views += i < x ? 1 : 0;
	i = x;
	while (++i < map_w && map[y][i] != '#'); // check if asteroid on the right of the x position on actual y
	views += i < map_w ? 1 : 0;
	return (views);
}

int		main(int ac, char **av)
{
	char	*line;
	int		y;
	int		x;
	int		views;
	int		max_views;

	if (ac != 2)
		return (0);
	int fd = open(av[1], O_RDONLY);
	map_h = 0;
	while (get_next_line(fd, &line) == 1)
		map[map_h++] = line;
	map_w = 0;
	while (map[0][map_w])
		map_w++;
	y = -1;
	max_views = 0;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (map[y][x] == '#')
			{
				views = count_views(map, y, x);
				if (views > max_views)
					max_views = views;
			}
		}
	}
	printf("result = %d\n", max_views);
	return(0);
}



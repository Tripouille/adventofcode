/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day10_part1.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 11:27:17 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 12:59:41 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		get_next_line(int fd, char **line);

char	*map[100];
int		map_w;
int		map_h;

int		count_views(char **map, int y, int x)
{
	int		count;
	int		i_x;

	count = 0;
	i_x = y;
	while (i_x < map_w)
	{
		while ()
		{


		}
	}
}

int		main(void)
{
	char	*line;
	int		fd = open("day10_input.txt", O_RDONLY);
	int		y;
	int		x;
	int		views;
	int		max_views;

	map_h = 0;
	while (get_next_line(fd, &line) == 1)
		map[map_h++] = line;
	map_w = 0;
	while (map[0][map_w])
		map_w++;
	y = -1;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			views = count_views(map, y, x);
			if (views > max_views)
				max_views = views;
		}
	}
	return(0);
}

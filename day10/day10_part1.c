/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day10_part1.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 11:27:17 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 12:52:41 by aalleman    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		get_next_line(int fd, char **line);

char	*map[100];
int		map_w;
int		map_h;

int		is_in_array(double *array, double number)
{
	int		i;

	i = -1;
	while (array[++i])
		if (array[i] == number)
			return (1);
	return (0);
}

int		count_diagonal_views(char **map, int y_base, int x_base)
{
	int		i;
	int		count;
	double	ratios1[500] = {0};
	double	ratios2[500] = {0};
	double	ratio;
	int		x;
	int		y;

	// Le calcul est separe en face nord/face sud car le ratio est le meme pour une meme droite prolongee d'en haut a gauche a en bas a droite, alors que le point de vue lui n'est pas le meme.
	i = 0;
	y = -1;
	while (++y < y_base)
	{
		x = -1;
		while (++x < map_w)
		{
			if (y != y_base && x != x_base && map[y][x] == '#')
			{
				ratio = (double)(y_base - y) / (x - x_base);
				if (!is_in_array(ratios1, ratio))
				{
					ratios1[i] = ratio;
					i++;
				}
			}
		}
	}
	count = i;
	i = 0;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (y != y_base && x != x_base && map[y][x] == '#')
			{
				ratio = (double)(y_base - y) / (x - x_base);
				if (!is_in_array(ratios2, ratio))
				{
					ratios2[i] = ratio;
					i++;
				}
			}
		}
	}
	count += i;
	return (count);
}

int		count_views(char **map, int y, int x)
{
	int		i;
	int		count;

	count = count_diagonal_views(map, y, x);
	// Reste a compter les vues sur les points cardinaux :
	i = 0;
	while (i < x && map[y][i] != '#')
		i++;
	if (i < x)
		count++;
	i = x + 1;
	while (i < map_w && map[y][i] != '#')
		i++;
	if (i < map_w)
		count++;
	i = 0;
	while (i < y && map[i][x] != '#')
		i++;
	if (i < y)
		count++;
	i = y + 1;
	while (i < map_h && map[i][x] != '#')
		i++;
	if (i < map_h)
		count++;
	return (count);
}

int		main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		y;
	int		x;
	int		views;
	int		max_views;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
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



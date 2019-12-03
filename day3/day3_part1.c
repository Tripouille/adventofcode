/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day3.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/03 11:37:12 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/03 12:44:46 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define ABS(x) (x < 0 ? -(x) : x)

typedef struct		s_pos
{
	int		x;
	int		y;
}					t_pos;

t_pos		inter;

int		get_next_line(int fd, char **line);

void	actualize_inter(t_pos *pos)
{
	int		delta;
	int		old_delta;

	delta = ABS(49999 - pos->x) + ABS(49999 - pos->y);
	old_delta = ABS(49999 - inter.x) + ABS(49999 - inter.y);
	if (delta < old_delta)
	{
		inter.x = pos->x;
		inter.y = pos->y;
	}
}

void	draw(char map[100000][100000], t_pos *pos, char dir, int value, int id)
{
	while (value--)
	{
		if (dir == 'R')
			pos->x++;
		else if (dir == 'U')
			pos->y--;
		else if (dir == 'L')
			pos->x--;
		else
			pos->y++;
		if (map[pos->x][pos->y] && map[pos->x][pos->y] != id)
			actualize_inter(pos);
		map[pos->x][pos->y] = id;
	}
}

void	draw_wire(char map[100000][100000], t_pos *pos, char *line, int id)
{
	int		i;

	i = 0;
	pos->x = 49999;
	pos->y = 49999;
	while (line[i])
	{
		draw(map, pos, line[i], atoi(line + i + 1), id);
		while (line[i] && line[i] != ',')
			i++;
		if (line[i] == ',')
			i++;
	}
	free(line);
}

int		main(int ac, char **av)
{
	static char	map[100000][100000];
	t_pos	pos;
	char	*line;
	int		fd;

	inter.x = -1;
	inter.y = -1;
	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	if (get_next_line(fd, &line) < 1)
		return (-1);
	draw_wire(map, &pos, line, 1);
	if (get_next_line(fd, &line) < 1)
		return (-1);
	draw_wire(map, &pos, line, 2);
	printf("distance = %d\n",ABS(49999 - inter.x) + ABS(49999 - inter.y));
	return(0);
}

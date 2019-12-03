/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day3_part2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/03 11:37:12 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/03 14:49:07 by jgambard    ###    #+. /#+    ###.fr     */
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

int		inter[100000][100000];
t_pos	inter_pos[100];
int		i_inter;

int		get_next_line(int fd, char **line);

/*int		get_inter(void)
{
	int		x;
	int		y;
	int		min;

	min = 100000;
	y = 0;
	while (y < 100000)
	{
		x = 0;
		while (x < 100000)
		{
			if (inter[x][y] && inter[x][y] < min)
				min = inter[x][y];
			x++;
		}
		y++;
	}
	return (min);
}*/

int		get_inter(void)
{
	int		min;

	min = 100000;
	while (i_inter--)
	{
		if (inter[inter_pos[i_inter].x][inter_pos[i_inter].y] && inter[inter_pos[i_inter].x][inter_pos[i_inter].y] < min)
			min = inter[inter_pos[i_inter].x][inter_pos[i_inter].y];
	}
	return (min);
}

void	draw(char map[100000][100000], t_pos *pos, char dir, int value, int id)
{
	static int	last_id = 0;
	static int	length = 0;

	if (last_id != id)
	{
		length = 0;
		last_id = id;
	}
	while (value--)
	{
		length++;
		if (dir == 'R')
			pos->x++;
		else if (dir == 'U')
			pos->y--;
		else if (dir == 'L')
			pos->x--;
		else
			pos->y++;
		if (map[pos->x][pos->y] && map[pos->x][pos->y] != id)
		{
			inter[pos->x][pos->y] += length;
			if (id == 2)
			{
				inter_pos[i_inter].x = pos->x;
				inter_pos[i_inter].y = pos->y;
				i_inter++;
			}
		}
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
}

int		main(int ac, char **av)
{
	static char	map[100000][100000];
	t_pos	pos;
	char	*line1;
	char	*line2;
	int		fd;

	i_inter = 0;
	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	if (get_next_line(fd, &line1) < 1)
		return (-1);
	draw_wire(map, &pos, line1, 1);
	if (get_next_line(fd, &line2) < 1)
		return (-1);
	draw_wire(map, &pos, line2, 2);
	draw_wire(map, &pos, line1, 1);
	free(line1);
	free(line2);
	printf("distance = %d\n", get_inter());
	return(0);
}

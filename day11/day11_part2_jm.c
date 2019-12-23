/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day11_part2_jm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 11:30:42 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/23 16:51:46 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define MAP_W 100
#define BLACK 0
#define WHITE 1
#define LEFT 0
#define RIGTH 1
#define EAST 0
#define NORTH 90
#define WEST 180
#define SOUTH 270

long	values[1000000];
char	b[1000000];
long	relative_base;
char	*map[MAP_W];
char	*map_mask[MAP_W];
int		pos_y;
int		pos_x;
int		robot_ang;

void	init_map(char **map, char c)
{
	int		y;
	int		x;

	y = -1;
	while (++y < MAP_W)
	{
		map[y] = malloc(MAP_W);
		x = -1;
		while (++x < MAP_W)
			map[y][x] = c;
	}
}

void	show_map()
{
	int		y;

	y = -1;
	while (++y < MAP_W)
	{
		write(1, map[y], MAP_W);
		write(1, "\n", 1);
	}
}

long	*get_addr(int param_mode, int param_pos)
{
	if (param_mode == 0) //position mode
		return (values + values[param_pos]);
	if (param_mode == 1)
		return (values + param_pos);
	if (param_mode == 2) //relative mode
		return (values + relative_base + values[param_pos]);
	return (0);
}

int		robot_cam(void)
{
	if (map[pos_y][pos_x] == '.')
		return (BLACK);
	else
		return (WHITE);
}

void	robot_move(int *robot_cmd)
{
	if (*robot_cmd == BLACK)
	{
		map[pos_y][pos_x] = '.';
		if (pos_y == MAP_W / 2 - 1 && pos_x == MAP_W / 2 - 1)
			map_mask[pos_y][pos_x] = '.';
	}
	else if (*robot_cmd == WHITE)
	{
		map[pos_y][pos_x] = '#';
		map_mask[pos_y][pos_x] = '#';
	}
	else
		printf("ERROR\n");
	if (robot_ang == EAST)
	{
		if (robot_cmd[1] == LEFT)
		{
			robot_ang = NORTH;
			pos_y--;
		}
		else
		{
			robot_ang = SOUTH;
			pos_y++;
		}
	}
	else if (robot_ang == NORTH)
	{
		if (robot_cmd[1] == LEFT)
		{
			robot_ang = WEST;
			pos_x--;
		}
		else
		{
			robot_ang = EAST;
			pos_x++;
		}
	}
	else if (robot_ang == WEST)
	{
		if (robot_cmd[1] == LEFT)
		{
			robot_ang = SOUTH;
			pos_y++;
		}
		else
		{
			robot_ang = NORTH;
			pos_y--;
		}
	}
	else if (robot_ang == SOUTH)
	{
		if (robot_cmd[1] == LEFT)
		{
			robot_ang = EAST;
			pos_x++;
		}
		else
		{
			robot_ang = WEST;
			pos_x--;
		}
	}
}

void	do_it(void)
{
	long		i;
	long		*value1;
	long		*value2;
	long		*value3;
	int		robot_cmd[2];
	int		robot_cmd_id = 0;

	i = 0;
	while (values[i] != 99)
	{
		value1 = get_addr((values[i] / 100) % 10, i + 1);
		value2 = get_addr((values[i] / 1000) % 10, i + 2);
		value3 = get_addr((values[i] / 10000) % 10, i + 3);
		if (values[i] % 100 == 1) //OPCODE 1 AJOUTE LES 2 NOMBRES QUI SUIVENT
		{
			*value3 = *value1 + *value2;
			i += 4;
		}
		else if (values[i] % 100 == 2) //OPCODE 2 MULTIPLI LES 2 NOMBRES QUI SUIVENT
		{
			*value3 = *value1 * *value2;
			i += 4;
		}
		else if (values[i] % 100 == 3) //Stock un input dans l'adresse qui suit
		{
			*value1 = robot_cam();
			i += 2;
		}
		else if (values[i] % 100 == 4) //Output la valeur de l'adresse suivante
		{
			robot_cmd[robot_cmd_id++] = *value1;
			if (robot_cmd_id == 2)
			{
				robot_cmd_id = 0;
				robot_move(robot_cmd);
			}
			i += 2;
		}
		else if (values[i] % 100 == 5) //jump if true au parametre suivant
		{
			if (*value1)
				i = *value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 6) //jump if false
		{
			if (!*value1)
				i = *value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 7) //1 if less than
		{
			*value3 = *value1 < *value2 ? 1 : 0;
			i += 4;
		}
		else if (values[i] % 100 == 8) //1 if equals
		{
			*value3 = *value1 == *value2 ? 1 : 0;
			i += 4;
		}
		else if (values[i] % 100 == 9)
		{
			relative_base += *value1;
			i += 2;
		}
	}
}



int		count(void)
{
	int		y;
	int		x;
	int		count;

	y = -1;
	count = 0;
	while (++y < MAP_W)
	{
		x = -1;
		while (++x < MAP_W)
			if (map_mask[y][x] == '#')
				count++;
	}
	if (map_mask[MAP_W / 2 - 1][MAP_W / 2 - 1] == '.')
		count++;
	return (count);
}

int		main(int ac, char **av)
{
	char			*buffer = b;
	long			i;
	int				fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 1000000);
	i = 0;
	while (*buffer != '\n')
	{
		values[i++] = atol(buffer);
		while (isdigit(*buffer) || *buffer == '-')
			buffer++;
		if (*buffer == ',')
			buffer++;
	}
	relative_base = 0;
	init_map(map, '.');
	init_map(map_mask, '.');
	pos_y = MAP_W / 2 - 1;
	pos_x = MAP_W / 2 - 1;
	map[pos_y][pos_x] = '#';
	map_mask[pos_y][pos_x] = '#';
	robot_ang = NORTH;
	do_it();
	printf("Result = %i\n", count());
	show_map();
	return(0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day13_part1_jm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tripouille <marvin@le-101.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/27 14:03:53 by tripouil     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/27 15:42:01 by tripouil    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
enum {EMPTY, WALL, BLOCK, HORIZONTAL_PADDLE, BALL};
long	values[10000];
long	relative_base;
long	blocks;

long	*get_addr(int param_mode, int param_pos)
{
	if (param_mode == 0)
		return (values + values[param_pos]);
	if (param_mode == 1)
		return (values + param_pos);
	if (param_mode == 2)
		return (values + relative_base + values[param_pos]);
	return (0);
}

void	do_it(void)
{
	long		i;
	long		*value1;
	long		*value2;
	long		*value3;
	char		b;
	int			i_infos;

	i = 0;
	i_infos = 0;
	while (values[i] != 99)
	{
		value1 = get_addr((values[i] / 100) % 10, i + 1);
		value2 = get_addr((values[i] / 1000) % 10, i + 2);
		value3 = get_addr((values[i] / 10000) % 10, i + 3);
		if (values[i] % 100 == 1)
		{
			*value3 = *value1 + *value2;
			i += 4;
		}
		else if (values[i] % 100 == 2)
		{
			*value3 = *value1 * *value2;
			i += 4;
		}
		else if (values[i] % 100 == 3)
		{
			read(0, &b, 1);
			*value1 = b;
			i += 2;
		}
		else if (values[i] % 100 == 4)
		{
			i_infos++;
			if (!(i_infos % 3) && *value1 == BLOCK)
					blocks++;
			i += 2;
		}
		else if (values[i] % 100 == 5)
		{
			if (*value1)
				i = *value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 6)
		{
			if (!*value1)
				i = *value2;
			else
				i += 3;
		}
		else if (values[i] % 100 == 7)
		{
			*value3 = *value1 < *value2 ? 1 : 0;
			i += 4;
		}
		else if (values[i] % 100 == 8)
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

int		main(int ac, char **av)
{
	char			b[1000000];
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
	blocks = 0;
	do_it();
	printf("result = %li\n", blocks);
	return(0);
}

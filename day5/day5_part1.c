/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day5_part1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 19:01:13 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 19:43:03 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int		values[100000];
char	b[10000];

void	do_it(void)
{
	int		i;
	int		value1;
	int		value2;
	char	b[100];
	int		ret;

	i = 0;
	while (values[i] != 99)
	{
		if ((values[i] / 100) % 10 == 0)
			value1 = values[values[i + 1]];
		else
			value1 = values[i + 1];
		if ((values[i] / 1000) % 10 == 0)
			value2 = values[values[i + 2]];
		else
			value2 = values[i + 2];
		if (values[i] % 100 == 1)
		{
			values[values[i + 3]] = value1 + value2;
			i += 4;
		}
		else if (values[i] % 100 == 2)
		{
			values[values[i + 3]] = value1 * value2;
			i += 4;
		}
		else if (values[i] % 100 == 3)
		{
			dprintf(1, "Input : \n");
			ret = read(0, b, 100);
			values[values[i + 1]] = atoi(b);
			i += 2;
		}
		else if (values[i] % 100 == 4)
		{
			printf("\nOutput : %d\n", value1);
			i += 2;
		}
	}
}

int		main(int ac, char **av)
{
	char			*buffer = b;
	int				i;
	int				fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 10000);
	i = 0;
	while (*buffer != '\n')
	{
		values[i++] = atoi(buffer);
		while (isdigit(*buffer) || *buffer == '-')
			buffer++;
		if (*buffer == ',')
			buffer++;
	}
	do_it();
	return(0);
}

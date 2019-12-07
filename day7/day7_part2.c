/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day7_part2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 19:01:13 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/07 16:15:27 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define NEXT(nb) nb = nb < 4 ? nb + 1 : 0
#define PREV(nb) nb == 0 ? 4 : nb - 1

long		values[5][100000];

void	do_it(void)
{
	long		value1;
	long		value2;
	long		position[5];
	long		ampli_nb;
	long		prev_output[5];
	long		result;

	ampli_nb = -1;
	while (++ampli_nb < 5)
	{
		position[ampli_nb] = 2;
		prev_output[ampli_nb] = -1;
	}
	prev_output[4] = 0;
	ampli_nb = 0;
	while (values[4][position[4]] != 99)
	{
		//printf("ampli_nb : %ld\n", ampli_nb);
		//printf("debug : %d\n", values[4][position[4]]);
		//printf("ampli_nb : %d, position[ampli_nb] : %d, case : %d\n", ampli_nb, position[ampli_nb], values[ampli_nb][position[ampli_nb]]);
		if (values[ampli_nb][position[ampli_nb]] % 100 == 99)
		{
			//printf("next1\n");
			NEXT(ampli_nb);
			continue;
		}
		if ((values[ampli_nb][position[ampli_nb]] / 100) % 10 == 0)
			value1 = values[ampli_nb][values[ampli_nb][position[ampli_nb] + 1]];
		else
			value1 = values[ampli_nb][position[ampli_nb] + 1];
		if ((values[ampli_nb][position[ampli_nb]] / 1000) % 10 == 0)
			value2 = values[ampli_nb][values[ampli_nb][position[ampli_nb] + 2]];
		else
			value2 = values[ampli_nb][position[ampli_nb] + 2];
		if (values[ampli_nb][position[ampli_nb]] % 100 == 1)
		{
			values[ampli_nb][values[ampli_nb][position[ampli_nb] + 3]] = value1 + value2;
			position[ampli_nb] += 4;
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 2)
		{
			values[ampli_nb][values[ampli_nb][position[ampli_nb] + 3]] = value1 * value2;
			position[ampli_nb] += 4;
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 3)
		{
			if (prev_output[PREV(ampli_nb)] != -1)
			{
				values[ampli_nb][values[ampli_nb][position[ampli_nb] + 1]] = prev_output[PREV(ampli_nb)];
				prev_output[PREV(ampli_nb)] = -1;
				position[ampli_nb] += 2;
			}
			else
			{
				//printf("next2\n");
				NEXT(ampli_nb);
			}
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 4)
		{
			//printf("value1 : %ld\n", value1);
			if (ampli_nb == 4)
			{
				result = value1;
			}
			//printf("%d", value1);
			prev_output[ampli_nb] = value1;
			position[ampli_nb] += 2;
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 5)
		{
			if (value1)
				position[ampli_nb] = value2;
			else
				position[ampli_nb] += 3;
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 6)
		{
			if (!value1)
				position[ampli_nb] = value2;
			else
				position[ampli_nb] += 3;
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 7)
		{
			if (value1 < value2)
				values[ampli_nb][values[ampli_nb][position[ampli_nb] + 3]] = 1;
			else
				values[ampli_nb][values[ampli_nb][position[ampli_nb] + 3]] = 0;
			position[ampli_nb] += 4;
		}
		else if (values[ampli_nb][position[ampli_nb]] % 100 == 8)
		{
			if (value1 == value2)
				values[ampli_nb][values[ampli_nb][position[ampli_nb] + 3]] = 1;
			else
				values[ampli_nb][values[ampli_nb][position[ampli_nb] + 3]] = 0;
			position[ampli_nb] += 4;
		}
	}
	printf("%ld", prev_output[4]);
}

int		main(int ac, char **av)
{
	char	b[10000];
	char	*buffer = b;
	int		i;
	int		ampli_nb;
	int		fd;
	int		value;
	char	c;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 10000);
	i = 0;
	while (*buffer != '\n')
	{
		value = atoi(buffer);
		ampli_nb = -1;
		while (++ampli_nb < 5)
			values[ampli_nb][i] = value;
		i++;
		while (isdigit(*buffer) || *buffer == '-')
			buffer++;
		if (*buffer == ',')
			buffer++;
	}
	ampli_nb = -1;
	while (++ampli_nb < 5)
	{
		read(0, &c, 1);
		values[ampli_nb][values[ampli_nb][1]] = c - '0';
	}
	do_it();
	return(0);
}

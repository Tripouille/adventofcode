/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day2.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/02 11:54:49 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/02 12:14:33 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void	do_it(int *values)
{
	int		i;

	i = 0;
	values[1] = 12;
	values[2] = 2;
	while (values[i] != 99)
	{
		if (values[i] == 1)
			values[values[i + 3]] = values[values[i + 1]] + values[values[i + 2]];
		else if (values[i] == 2)
			values[values[i + 3]] = values[values[i + 1]] * values[values[i + 2]];
		i += 4;
	}
}

int		main(int ac, char **av)
{
	int		values[1000];
	char	b[1000];
	char	*buffer = b;
	int		i;
	int		fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 1000);
	i = 0;
	while (*buffer != '\n')
	{
		values[i++] = atoi(buffer);
		while (isdigit(*buffer))
			buffer++;
		if (*buffer == ',')
			buffer++;
	}
	do_it(values);
	printf("result = %d\n", *values);
	return(0);
}

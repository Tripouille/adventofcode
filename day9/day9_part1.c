/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day9_part1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/09 11:30:42 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/09 13:27:02 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

long	values[1000000];
char	b[100000];
long	relative_base;

long	*get_addr(int param_mode, int param_pos)
{
	if (param_mode == 0)
		return (values + values[param_pos]);
	if (param_mode == 1)
		return (values + param_pos);
	if (param_mode == 2)
		return (values + values[param_pos] + relative_base);
	return (0);
}

void	do_it(void)
{
	long		i;
	long		*value1;
	long		*value2;
	long		*value3;
	char		b[100];
	//int			boom = 0;

	i = 0;
	//printf("value = %li\n" , values[0]);
	while (values[i] != 99)
	{
		//if (++boom == 7)
			//break ;
		//printf("i = %li\n", i);
		//printf("value = %li\n" , values[i]);
		//printf("value 0  = %li\n" , values[0]);
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
			dprintf(2, "input :\n");
			read(0, b, 100);
			*value1 = atol(b);
			i += 2;
		}
		else if (values[i] % 100 == 4)
		{
			printf("output: %li\n", *value1);
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
			if (*value1 < *value2)
				*value3 = 1;
			else
				*value3 = 0;
			i += 4;
		}
		else if (values[i] % 100 == 8)
		{
			if (*value1 == *value2)
				*value3 = 1;
			else
				*value3 = 0;
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
	char			*buffer = b;
	long			i;
	int				fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, 100000);
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
	do_it();
	return(0);
}

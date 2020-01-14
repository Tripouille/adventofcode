/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day16_part1_astrid.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chinimala <marvin@le-101.fr>               +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 16:53:19 by chinimal     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 17:23:06 by chinimal    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	values[10000000];
int		pattern[4];

void	one_phase(void)
{
	long	result;
	long	i;
	long	j;
	int		i_pattern;
	int		pattern_repetition;

	i = 0;
	while (values[i])
	{
		result = 0;
		i_pattern = 1;
		pattern_repetition = 0;
		j = i;
		while (values[j])
		{
			result += (values[j] - '0') * pattern[i_pattern];
			pattern_repetition++;
			if (pattern_repetition == i + 1)
			{
				pattern_repetition = 0;
				i_pattern = i_pattern == 3 ? 0 : i_pattern + 1;
			}
			j++;
		}
		values[i] = (result < 0 ? -result : result) % 10 + '0';
		i++;
	}
}

void	set_pattern(void)
{
	pattern[0] = 0;
	pattern[1] = 1;
	pattern[2] = 0;
	pattern[3] = -1;
}

int		main(int ac, char **av)
{
	int		fd;
	int		ret;
	int		i;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	ret = read(fd, values, 10000000);
	values[ret - 1] = 0;
	set_pattern();
	i = 0;
	while (i < 100)
	{
		one_phase();
		i++;
	}
	write(1, values, 8);
	write(1, "\n", 1);
	return(0);
}

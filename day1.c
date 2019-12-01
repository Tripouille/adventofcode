/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/01 13:17:49 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/01 13:34:46 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int		get_next_line(int fd, char **line);

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	long	result;

	if (ac != 2)
		return (-1);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	result = 0;
	line = 0;
	while (get_next_line(fd, &line) == 1)
	{
		if (atoi(line))
			result += atoi(line) / 3 - 2;
		free(line);
	}
	if (atoi(line))
		result += atoi(line) / 3 - 2;
	free(line);
	printf("%li\n", result);
	return (0);
}

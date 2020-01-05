#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
# define ABS(x) (x < 0 ? -x : x)

void	do_it(char *buffer, int *filter)
{
	int 	tmp[1000000] = {0};
	int		i;
	int		j;
	int		n;
	int		i_filter;

	i = -1;
	while (buffer[++i] != '\n')
	{
		i_filter = 0;
		n = 0;
		j = -1;
		while (buffer[++j] != '\n')
		{
			if (++n > i)
			{
				i_filter = i_filter + 1 < 4 ? i_filter + 1 : 0;
				n = 0;
			}
			tmp[i] += (buffer[j] - '0') * filter[i_filter];
		}
		tmp[i] = ABS(tmp[i]) % 10 + '0';
	}
	i = -1;
	while (buffer[++i] != '\n')
		buffer[i] = tmp[i];
}

int		main(int ac, char **av)
{
	int		fd;
	char	buffer[1000000] = {0};
	int		filter[4];

	filter[0] = 0;
	filter[1] = 1;
	filter[2] = 0;
	filter[3] = -1;
	if (ac != 2)
		return (-1);
	fd = open(av[1], O_RDONLY);
	read(fd, buffer, 1000000);
	int		n = -1;
	while (++n < 100)
		do_it(buffer, filter);
	write(1, buffer, 8);
	return (0);
}

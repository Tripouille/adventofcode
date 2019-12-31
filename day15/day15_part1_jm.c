#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

long	values[10000];
long	relative_base;

enum {RWALL, RPATH, RFOUND};
enum {DIRE = 0, DONE};
#define EAST 4
int		direction;
int		droid_ret;
char	path[10000][4] = {0};
int		i_path = 0;
long	min_steps = 1000000000;

int		inverse_dir(int dir)
{
	return (dir % 2 ? dir + 1 : dir - 1);
}

void	add_possib(int dire)
{
	int 	i;

	i = -1;
	while (path[i_path][++i]);
	path[i_path][i] = dire;
}

void	next()
{
	int		i;

	i = -1;
	while (path[i_path][++i])
		path[i_path][i] = path[i_path][i + 1];
}

void	set_direction(void)
{
	int				i;
	static char		scan[2] = {0};

	if (scan[DIRE] > 0 && scan[DONE])
	{
		scan[DONE] = 0;
		direction = inverse_dir(scan[DIRE]);
		if (droid_ret != RWALL)
			add_possib(scan[DIRE]);
		if (droid_ret == RFOUND)
			min_steps = i_path + 1 < min_steps ? i_path + 1 : min_steps;
		if (droid_ret != RWALL)
			return ; 
	}
	if (++scan[DIRE] <= EAST && i_path && scan[DIRE] == inverse_dir(path[i_path - 1][0])) // si check sur nos pas on saute.
		++scan[DIRE];
	if (scan[DIRE] > EAST) // si check fini.
		scan[DIRE] = 0;
	if (scan[DIRE])
	{
		scan[DONE] = 1;
		direction = scan[DIRE];
		return ;
	}
	if (path[i_path][0])
		direction = path[i_path++][0];
	else
	{
		direction = inverse_dir(path[--i_path][0]); //On revien sur la case précedente.
		next(); // On next celui d'avant.
		scan[DIRE] = -1; // rewind pas de scan.
	}
}

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
	char		b[10];
	int			infos[3];
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
			set_direction();
			*value1 = direction;
			i += 2;
		}
		else if (values[i] % 100 == 4)
		{
			droid_ret = *value1;
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
	relative_base = 0;
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
	do_it();
	printf("result = %li.\n", min_steps);
	return(0);
}

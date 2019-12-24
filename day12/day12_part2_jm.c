/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day12_part2_jm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 17:55:26 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/24 13:28:01 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#define BUFFER_SIZE 10000
#define ABS(x) (x < 0 ? -x : x)

typedef struct		s_moon
{
	int		pos_x;
	int		pos_y;
	int		pos_z;

	int		vel_x;
	int		vel_y;
	int		vel_z;
}					t_moon;

t_moon		moons[4];
t_moon		initial_moons[4];
int			moon_time[4][100000];

void	set_value(char **s, int *p)
{
		while (**s != '=')
			++*s;
		*p = atol(++*s);
		while (**s == '-' || isdigit(**s))
			++*s;
}

void	do_it()
{
	int		i_moon;
	int		i;

	i_moon = -1;
	while (++i_moon < 4)
	{
		i = -1;
		while (++i < 4)
		{
			if (i_moon != i)
			{
				if (moons[i].pos_x < moons[i_moon].pos_x)
					moons[i_moon].vel_x--;
				else if (moons[i].pos_x != moons[i_moon].pos_x)
					moons[i_moon].vel_x++;
				if (moons[i].pos_y < moons[i_moon].pos_y)
					moons[i_moon].vel_y--;
				else if (moons[i].pos_y != moons[i_moon].pos_y)
					moons[i_moon].vel_y++;
				if (moons[i].pos_z < moons[i_moon].pos_z)
					moons[i_moon].vel_z--;
				else if (moons[i].pos_z != moons[i_moon].pos_z)
					moons[i_moon].vel_z++;
			}
		}
	}
	while (--i_moon >= 0)
	{
		moons[i_moon].pos_x += moons[i_moon].vel_x;
		moons[i_moon].pos_y += moons[i_moon].vel_y;
		moons[i_moon].pos_z += moons[i_moon].vel_z;
	}
}

int		count()
{
	int		i_moon;
	int		result;

	result = 0;
	i_moon = -1;
	while (++i_moon < 4)
		result += (ABS(moons[i_moon].pos_x) + ABS(moons[i_moon].pos_y) + ABS(moons[i_moon].pos_z))
		* (ABS(moons[i_moon].vel_x) + ABS(moons[i_moon].vel_y) + ABS(moons[i_moon].vel_z));
	return (result);
}

int		fini()
{
	int		i_moon;

	i_moon = -1;
	while (++i_moon < 4)
		if (initial_moons[i_moon].pos_x != moons[i_moon].pos_x
		|| initial_moons[i_moon].pos_y != moons[i_moon].pos_y
		|| initial_moons[i_moon].pos_z != moons[i_moon].pos_z)
			return (0);
	return (1);
}

void	show_time(int *moon_time, int n)
{
	while (n--)
		printf("%i, ", *moon_time++);
	printf("\n");

}

int		main(int ac, char **av)
{
	char			b[BUFFER_SIZE];
	char			*buffer = b;
	long			i_moon;
	int				fd;
	unsigned long			i;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	read(fd, b, BUFFER_SIZE);
	i_moon = -1;
	while (++i_moon < 4)
	{
		set_value(&buffer, &(moons[i_moon].pos_x));
		initial_moons[i_moon].pos_x = moons[i_moon].pos_x;
		set_value(&buffer, &(moons[i_moon].pos_y));
		initial_moons[i_moon].pos_y = moons[i_moon].pos_y;
		set_value(&buffer, &(moons[i_moon].pos_z));
		initial_moons[i_moon].pos_z = moons[i_moon].pos_z;
	}
	i = 1;
	do_it();
	int		last_time[4] = {0};
	int		im[4] = {0};
	while (i < 100000000)
	{
		i_moon = -1;
		while (++i_moon < 1)
			if (initial_moons[i_moon].pos_x == moons[i_moon].pos_x
			&& initial_moons[i_moon].pos_y == moons[i_moon].pos_y
			&& initial_moons[i_moon].pos_z == moons[i_moon].pos_z)
			{
				moon_time[i_moon][im[i_moon]++] = i - last_time[i_moon];
				last_time[i_moon] = i;
			}
		i++;
		do_it();
	}
	show_time(moon_time[0], 30);
	printf("\n");
	//show_time(moon_time[1], 30);
	//printf("\n");
	//show_time(moon_time[2], 30);
	//printf("\n");
	//show_time(moon_time[3], 30);
	//printf("\n");
	//printf("Result = %li\n", i);
	return(0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day12_part2_jm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/23 17:55:26 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/26 19:10:47 by tripouil    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include "libmath.h"
#define BUFFER_SIZE 10000
#define X 0
#define Y 1
#define Z 2
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
int			moons_period[3][100000];
int			last_time[3] = {0};
int			imp[3] = {0};

/*
** Parsing
*/

void	set_value(char **s, int *p)
{
		while (**s != '=')
			++*s;
		*p = atol(++*s);
		while (**s == '-' || isdigit(**s))
			++*s;
}

/*
** Simulate the fucking universe ma biche
*/

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

/*
** Check if the actual interval has already occured
** if not return 0 if yes it will add all previous interval
** to determine the period of the axis.
*/

int		get_period(int axis, int actual_time)
{
	int		result;

	result = 0;
	moons_period[axis][imp[axis]] = actual_time - last_time[axis];
	last_time[axis] = actual_time;
	if (imp[axis] && moons_period[axis][imp[axis]] == moons_period[axis][0])
		while (imp[axis]-- >= 0)
			result += moons_period[axis][imp[axis]];
	imp[axis]++;
	return (result);
}

/*
** Clean enought for your smart mind.
*/

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
	do_it();
	i = 1;
	int		period_x = 0;
	int		period_y = 0;
	int		period_z = 0;
	while (!period_x || !period_y || !period_z)
	{
		if (!period_x
		&& initial_moons[0].pos_x == moons[0].pos_x
		&& initial_moons[1].pos_x == moons[1].pos_x
		&& initial_moons[2].pos_x == moons[2].pos_x
		&& initial_moons[3].pos_x == moons[3].pos_x)
			period_x = get_period(X, i);
		if (!period_y
		&& initial_moons[0].pos_y == moons[0].pos_y
		&& initial_moons[1].pos_y == moons[1].pos_y
		&& initial_moons[2].pos_y == moons[2].pos_y
		&& initial_moons[3].pos_y == moons[3].pos_y)
			period_y = get_period(Y, i);
		if (!period_z
		&& initial_moons[0].pos_z == moons[0].pos_z
		&& initial_moons[1].pos_z == moons[1].pos_z
		&& initial_moons[2].pos_z == moons[2].pos_z
		&& initial_moons[3].pos_z == moons[3].pos_z)
			period_z = get_period(Z, i);
		i++;
		do_it();
	}
	printf("period_x = %i period_y = %i period_z = %i\n", period_x, period_y, period_z);
	printf("result = %li\n", lcm(3, period_x, period_y, period_z)); // least common multiple des trois merdes
	return(0);
}

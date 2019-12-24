/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day10_part2_jm.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 11:27:17 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/24 12:42:10 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#define SCAN 0
#define DESTROY 1
#define ABS(x) (x < 0 ? -x : x)

typedef struct		s_ast
{
	int			y;
	int			x;
	double		tan;
}					t_ast;

int		get_next_line(int fd, char **line);

char	*map[100];
int		map_w;
int		map_h;
int		laser_y;
int		laser_x;
t_ast	destroyed_ast[1000];
int		i_destroyed_ast;

void	actualize_ast(double t, int y, int x, t_ast *a)
{
	while (a->tan && a->tan != t)
		a++;
	a->tan = t;
	a->y = y;
	a->x = x;
}

void	init_ast(t_ast *a, t_ast **pa)
{
	int		i;

	i = -1;
	while (++i < 500)
	{
		pa[i] = a + i;
		a[i].tan = 0.0;
	}
}

void	swap(t_ast **p1, t_ast **p2)
{
	void	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void	sort_tan(t_ast **pa)
{
	int		i;
	int		j;

	i = -1;
	while (pa[++i]->tan)
	{
		j = i;
		while (pa[++j]->tan)
		{
			if (ABS(pa[i]->tan) < ABS(pa[j]->tan))
				swap(pa + i, pa + j);
		}
	}
}

void	destroy_ast(t_ast **pa)
{
	int		i;

	i = -1;
	while (pa[++i]->tan)
	{
		destroyed_ast[i_destroyed_ast].y = pa[i]->y;
		destroyed_ast[i_destroyed_ast].x = pa[i]->x;
		destroyed_ast[i_destroyed_ast++].tan = pa[i]->tan;
		map[pa[i]->y][pa[i]->x] = '.';
	}
}


int		ray_ne(int y, int x, int mode)
{
	t_ast		a[500];
	t_ast		*pa[500];
	double		t;
	int			checked_x;
	int			checked_y;
	int i;

	init_ast(a, pa);
	checked_x = map_w;
	while (--checked_x >= x)
	{
		checked_y = -1;
		while (++checked_y < y)
		{
			t = ((double)(y - checked_y) / (x - checked_x));
			if (map[checked_y][checked_x] == '#')
				actualize_ast(t, checked_y, checked_x, a);
		}
	}
	i = -1;
	while (pa[++i]->tan);
	if (mode == DESTROY)
	{
		sort_tan(pa);
		destroy_ast(pa);
	}
	return (i);
}

int		ray_se(int y, int x, int mode)
{
	t_ast		a[500];
	t_ast		*pa[500];
	double		t;
	int			checked_x;
	int			checked_y;
	int i;

	init_ast(a, pa);
	checked_x = map_w;
	while (--checked_x > x)
	{
		checked_y = map_h;
		while (--checked_y >= y)
		{
			t = (double)(x - checked_x) / (y - checked_y);
			if (map[checked_y][checked_x] == '#')
				actualize_ast(t, checked_y, checked_x, a);
		}
	}
	i = -1;
	while (pa[++i]->tan);
	if (mode == DESTROY)
	{
		sort_tan(pa);
		destroy_ast(pa);
	}
	return (i);
}

int		ray_sw(int y, int x, int mode)
{
	t_ast		a[500];
	t_ast		*pa[500];
	double		t;
	int			checked_x;
	int			checked_y;
	int i;

	init_ast(a, pa);
	checked_x = -1;
	while (++checked_x <= x)
	{
		checked_y = map_h;
		while (--checked_y > y)
		{
			t = (double)(y - checked_y) / (x - checked_x);
			if (map[checked_y][checked_x] == '#')
				actualize_ast(t, checked_y, checked_x, a);
		}
	}
	i = -1;
	while (pa[++i]->tan);
	if (mode == DESTROY)
	{
		sort_tan(pa);
		destroy_ast(pa);
	}
	return (i);
}


int		ray_nw(int y, int x, int mode)
{
	t_ast		a[500];
	t_ast		*pa[500];
	double		t;
	int			checked_x;
	int			checked_y;
	int			 i;

	init_ast(a, pa);
	checked_x = -1;
	while (++checked_x < x)
	{
		checked_y = -1;
		while (++checked_y <= y)
		{
			t = (double)(x - checked_x) / (y - checked_y);
			if (map[checked_y][checked_x] == '#')
				actualize_ast(t, checked_y, checked_x, a);
		}
	}
	i = -1;
	while (pa[++i]->tan);
	if (mode == DESTROY)
	{
		sort_tan(pa);
		destroy_ast(pa);
	}
	return (i);
}

int		ray(int y, int x, int mode)
{
	int		ast;

	ast = ray_ne(y, x, mode);
	ast += ray_se(y, x, mode);
	ast += ray_sw(y, x, mode);
	ast += ray_nw(y, x, mode);
	return (ast);
}

void	set_laser()
{
	int		y;
	int		x;
	int		views;
	int		max_views;

	y = -1;
	max_views = 0;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (map[y][x] == '#')
			{
				views = ray(y, x, SCAN);
				if (views > max_views)
				{
					laser_y = y;
					laser_x = x;
					max_views = views;
				}
			}
		}
	}
}

int		main(int ac, char **av)
{
	char	*line;
	if (ac != 2)
		return (0);
	int fd = open(av[1], O_RDONLY);
	map_h = 0;
	while (get_next_line(fd, &line) == 1)
		map[map_h++] = line;
	map_w = 0;
	while (map[0][map_w])
		map_w++;
	set_laser();
	i_destroyed_ast = 0;
	while (i_destroyed_ast < 200)
		ray(laser_y, laser_x, DESTROY);
	printf("result = %d\n", destroyed_ast[199].x * 100 + destroyed_ast[199].y);
	return(0);
}



/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day6_part1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 14:07:29 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 15:32:33 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct			s_node
{
	char			*name;
	int				p;
}						t_node;

int			get_next_line(int fd, char **line);

void		add(t_node *galaxy, char *parent, char *child)
{
	int		p;
	int		c;

	p = 0;
	while (galaxy[p].name && strcmp(galaxy[p].name, parent))
		p++;
	if (!galaxy[p].name)
		galaxy[p].name = parent;
	c = 0;
	while (galaxy[c].name && strcmp(galaxy[c].name, child))
		c++;
	if (!galaxy[c].name)
		galaxy[c].name = child;
	galaxy[c].p = p;
}

void		init(t_node *galaxy)
{
	int		i;

	i = -1;
	while (++i < 10000)
	{
		galaxy[i].name = 0;
		galaxy[i].p = -1;
	}
}

int			main(void)
{
	t_node		galaxy[10000];
	int			i;
	char		*line;
	int			fd = open("day6_input.txt", O_RDONLY);
	char		*planet1;
	char		*planet2;
	int			value;
	t_node		tmp;

	init(galaxy);
	while (get_next_line(fd, &line))
	{
		line[3] = 0;
		planet1 = line;
		planet2 = line + 4;
		add(galaxy, planet1, planet2);
	}
	i = -1;
	value = 0;
	while (galaxy[++i].name)
	{
		tmp = galaxy[i];
		while (tmp.p != -1)
		{
			tmp = galaxy[tmp.p];
			value++;
		}
	}
	printf("result = %i\n", value);
	return(0);
}

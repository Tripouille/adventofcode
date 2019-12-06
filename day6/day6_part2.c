/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day6_part2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 14:07:29 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 16:15:17 by jgambard    ###    #+. /#+    ###.fr     */
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

int			is_in_you_way(int *you_way, int to_find)
{
	int		i;

	i = 0;
	while (you_way[i] != -1 && you_way[i] != to_find)
		i++;
	return (you_way[i] != -1 ? i : -1);
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
	int			you_way[1000];
	int			ret;
	int			san_id = 0;
	int			you_id = 0;

	init(galaxy);
	while (get_next_line(fd, &line))
	{
		line[3] = 0;
		planet1 = line;
		planet2 = line + 4;
		add(galaxy, planet1, planet2);
	}
	i = 0;
	while (galaxy[you_id].name && strcmp(galaxy[you_id].name, "YOU"))
		you_id++;
	while (you_id != -1)
	{
		you_way[i++] = galaxy[you_id].p;
		you_id = galaxy[you_id].p;
	}
	while (galaxy[san_id].name && strcmp(galaxy[san_id].name, "SAN"))
		san_id++;
	value = 0;
	while ((ret = is_in_you_way(you_way, galaxy[san_id].p)) == -1)
	{
		san_id = galaxy[san_id].p;
		value++;
	}
	value += ret;
	printf("result = %i\n", value);
	return(0);
}

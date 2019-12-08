/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day8_part2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/08 12:09:28 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/08 13:31:47 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define IMAGE_SIZE 150

typedef struct		s_list
{
	char			data[IMAGE_SIZE + 1];
	struct s_list	*next;
}					t_list;

int		add_front(t_list **first)
{
	t_list		*new;

	if (!(new = malloc(sizeof(*new))))
		return (-1);
	new->data[IMAGE_SIZE] = 0;
	new->next = *first;
	*first = new;
	return (1);
}

void	purge(t_list **list)
{
	if (!*list)
		return ;
	purge(&(*list)->next);
	free(*list);
	*list = 0;
}

char	find_pixel(t_list *list, int i)
{
	char	pixel;

	pixel = '2';
	if (list->next)
		pixel = find_pixel(list->next, i);
	if (pixel == '2')
		return (list->data[i]);
	return (pixel);
}

int		main(void)
{
	t_list		*images;
	int			fd = open("day8_input.txt", O_RDONLY);
	int			i;
	char		c;

	images = 0;
	add_front(&images);
	while (read(fd, images->data, IMAGE_SIZE) == IMAGE_SIZE)
		add_front(&images);
	i = -1;
	while (++i < 150)
	{
		if (i && !(i % 25))
			write(1, "\n", 1);
		c = find_pixel(images->next, i);
		if (c == '0')
			c = ' ';
		write(1, &c, 1);
	}
	purge(&images);
	return(0);
}

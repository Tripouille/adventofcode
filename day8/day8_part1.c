/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day8_part1.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/08 12:09:28 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/08 12:42:49 by jgambard    ###    #+. /#+    ###.fr     */
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

t_list	*find_fewestz(t_list *list)
{
	t_list		*fewestz;
	int			i;
	int			z;
	int			z_min;

	z_min = 150;
	while (list)
	{
		z = 0;
		i = -1;
		while (list->data[++i])
			if (list->data[i] == '0')
				z++;
		if (z < z_min)
		{
			fewestz = list;
			z_min = z;
		}
		list = list->next;
	}
	return (fewestz);
}

int		do_it(t_list *list)
{
	int		i;
	int		uno;
	int		dos;

	i = -1;
	uno = 0;
	dos = 0;
	while (list->data[++i])
	{
		if (list->data[i] == '1')
			uno++;
		if (list->data[i] == '2')
			dos++;
	}
	return (uno * dos);
}

int		main(void)
{
	t_list		*images;
	int			fd = open("day8_input.txt", O_RDONLY);

	images = 0;
	add_front(&images);
	while (read(fd, images->data, IMAGE_SIZE) == IMAGE_SIZE)
		add_front(&images);
	printf("result = %i\n", do_it(find_fewestz(images->next)));
	purge(&images);
	return(0);
}

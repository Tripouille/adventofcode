/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day10_part2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aalleman <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/19 14:18:37 by aalleman     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/21 14:02:44 by aalleman    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

// Idee pour la partie 2 : une liste chainee ou chaque element est un ratio, et chaque ratio contient une liste chainee qui contient tous les asteroides detectes sur ce ratio. Quand un asteroide est detruit, l'element de liste chainee l'est aussi. Quand le dernier asteroide d'un ratio est detruit, l'element du ratio est detruit. Quand il n'y a plus aucun ratio, on a detruit tous les asteroides !
//
// Il faut donc trier les ratios au fur et a mesure ?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct		s_ast
{
	int				x;
	int				y;
	struct s_ast	*next;
}					t_ast;

typedef struct		s_view
{
	double			ratio;
	int				direction;
	t_ast			*list;
	struct s_view	*next;
}					t_view;

int		get_next_line(int fd, char **line);

char	*map[100];
t_view	*headviews1;
t_view	*headviews2;
int		map_w;
int		map_h;

t_view	*get_view(t_view *head, double number)
{
	while (head)
	{
		if (head->ratio == number)
			return (head);
		head = head->next;
	}
	return (0);
}

int		count_diagonal_views(char **map, int y_base, int x_base)
{
	int		i;
	int		count;
	double	ratio;
	t_view	*view;
	int		x;
	int		y;

	// Le calcul est separe en face nord/face sud car le ratio est le meme pour une meme droite prolongee d'en haut a gauche a en bas a droite, alors que le point de vue lui n'est pas le meme.
	i = 0;
	y = -1;
	while (++y < y_base)
	{
		x = -1;
		while (++x < map_w)
		{
			if (y != y_base && x != x_base && map[y][x] == '#')
			{
				ratio = (double)(y_base - y) / (x - x_base);
				view = get_view(headviews1, ratio);
				if (!view)
				{
					//creer view (au bon endroit selon le ratio), reaffecter view
				}
				//dans tous les cas, ajouter un asteroide a view (add front parce qu'il sera plus proche ?)

				/*if (!is_in_list(headviews1, ratio))
				{
					ratios1[i] = ratio;
					i++;
				}*/
			}
		}
	}
	count = i;
	i = 0;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (y != y_base && x != x_base && map[y][x] == '#')
			{
				ratio = (double)(y_base - y) / (x - x_base);
				if (!is_in_array(ratios2, ratio))
				{
					ratios2[i] = ratio;
					i++;
				}
			}
		}
	}
	count += i;
	return (count);
}

int		count_views(char **map, int y, int x)
{
	int		i;
	int		count;

	count = count_diagonal_views(map, y, x);
	// Reste a compter les vues sur les points cardinaux :
	i = 0;
	while (i < x && map[y][i] != '#')
		i++;
	if (i < x)
		count++;
	i = x + 1;
	while (i < map_w && map[y][i] != '#')
		i++;
	if (i < map_w)
		count++;
	i = 0;
	while (i < y && map[i][x] != '#')
		i++;
	if (i < y)
		count++;
	i = y + 1;
	while (i < map_h && map[i][x] != '#')
		i++;
	if (i < map_h)
		count++;
	return (count);
}

int		main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		y;
	int		x;
	int		views;
	int		max_views;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	map_h = 0;
	while (get_next_line(fd, &line) == 1)
		map[map_h++] = line;
	map_w = 0;
	while (map[0][map_w])
		map_w++;
	y = -1;
	while (++y < map_h)
	{
		x = -1;
		while (++x < map_w)
		{
			if (map[y][x] == '#')
			{
				views = count_views(map, y, x);
				if (views > max_views)
					max_views = views;
			}
		}
	}
	printf("result = %d\n", max_views);
	return(0);
}



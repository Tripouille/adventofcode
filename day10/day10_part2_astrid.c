#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define LIMIT 200 //Determine sur combien d'asteroides on tire, pour avoir les coordonnees du dernier

// Pour chacune des deux faces est/ouest, il existe une liste chainee (partant de headviews1 et headviews2).
// Chaque element de cette liste est associe a un ratio.
// Chacun de ces elements contient une liste chainee qui contient tous les asteroides detectes sur ce ratio.

// Ce programme stocke tous les ratios (dans l'ordre décroissant) avec leurs astéroïdes (du plus proche au plus loin),
// puis les destocke (pew pew) en les retirant de la liste.
// Leaks abondants.

typedef struct		s_ast
    {
    int				x; // Position de l'asteroide
    int				y;
    struct s_ast	*next;
}					t_ast;

typedef struct		s_view
    {
    double			ratio; // Coefficient directeur de la droite reliant l'asteroide de base et les asteroides sur cette vue
    t_ast			*list; // Liste des asteroides sur cette vue
    struct s_view	*next;
}					t_view;

int		get_next_line(int fd, char **line);

char	*map[100];
// Chaque element de ces tableaux de 500 cases correspond a un asteroide depuis lequel on regarde les autres.
// Lorsqu'on aura determine l'asteroide qui convient, les autres cases ne serviront plus pour les tirs de laser.
t_view	*headviews1[500] = {0};
t_view	*headviews2[500] = {0};
t_view  *headnorth[500] = {0};
t_view  *headeast[500] = {0};
t_view  *headsouth[500] = {0};
t_view  *headwest[500] = {0};
int		map_w;
int		map_h;


// PARTIE STOCKAGE

// Retourne soit un t_view deja existant pour ce ratio,
// soit un nouveau malloc
// bien range dans la liste chainee pour que toutes les vues soient triees par ordre decroissant de ratio.
// Si c'est un nouveau, alors count est incremente car c'est bien un nouvel asteroide a voir.
t_view	*get_view(t_view **head, double ratio, int *count)
{
    t_view  *node;
    t_view  *tmp;
    
    node = *head;
    while (node)
    {
        if (node->ratio == ratio)
        return (node);
        node = node->next;
    }
    (*count)++;
    node = malloc(sizeof(*node));
    node->ratio = ratio;
    node->list = 0;
    if (!*head || (*head)->ratio < ratio)
    {
        node->next = *head;
        *head = node;
        return (node);
    }
    tmp = *head;
    while (tmp->next)
    {
        if (tmp->next->ratio < ratio)
        {
            node->next = tmp->next;
            tmp->next = node;
            return (node);
        }
        tmp = tmp->next;
    }
    node->next = 0;
    tmp->next = node;
    return (node);
}

// Cree un nouvel asteroide dans la liste d'asteroides view->list,
// avec les coordonnes donnees.
// Si la vue n'existait pas, elle est cree : cela sert pour les points cardinaux (headnorth...).
void    new_asteroid(t_view **view, int x, int y)
{
    t_ast   *node;
    
    if (!*view)
    	*view = malloc(sizeof(t_view));
    node = malloc(sizeof(t_ast));
    node->x = x;
    node->y = y;
    node->next = (*view)->list;
    (*view)->list = node;
}

int     count_east_views(int i_head, int y_base, int x_base)
{
    int     y;
    int     x;
    t_view  *view;
    double  ratio;
    int     count;
    
    count = 0;
    x = map_w;
    while (--x > x_base)
    {
        y = -1;
        while (++y < map_h)
        {
            if (y != y_base && map[y][x] == '#')
            {
                ratio = (double)(y_base - y) / (x - x_base);
                view = get_view(&(headviews1[i_head]), ratio, &count);
                new_asteroid(&view, x, y);
            }
        }
    }
    return (count);
}

int     count_west_views(int i_head, int y_base, int x_base)
{
    int     y;
    int     x;
    t_view  *view;
    double  ratio;
    int     count;
    
    count = 0;
    x = -1;
    while (++x < x_base)
    {
        y = -1;
        while (++y < map_h)
        {
            if (y != y_base && map[y][x] == '#')
            {
                ratio = (double)(y_base - y) / (x - x_base);
                view = get_view(&(headviews2[i_head]), ratio, &count);
                new_asteroid(&view, x, y);
            }
        }
    }
    return (count);
}

int		count_views(int i_head, int y, int x)
{
    int		i;
    int     found;
    int		count;
    
    // Vues en diagonale
    count = count_east_views(i_head, y, x);
    count += count_west_views(i_head, y, x);
    // Reste a compter les vues sur les points cardinaux :
    // Dans chaque cas, on parcourt toutes les cases,
    // et on ajoute tous les asteroides trouves a headnorth, headsouth...
    // A chaque asteroide trouve, on incremente found. Si found != 0, count peut etre augmente de un.
    found = 0;
    i = -1;
    while (++i < x)
    	if (map[y][i] == '#' && ++found)
    		new_asteroid(&(headwest[i_head]), i, y);
    count += found ? 1 : 0;
    found = 0;
    i = map_w;
    while (--i > x)
    	if (map[y][i] == '#' && ++found)
    		new_asteroid(&(headeast[i_head]), i, y);
    count += found ? 1 : 0;
    found = 0;
    i = -1;
    while (++i < y)
    	if (map[i][x] == '#' && ++found)
    		new_asteroid(&(headnorth[i_head]), x, i);
    count += found ? 1 : 0;
    found = 0;
    i = map_h;
    while (--i > y)
    	if (map[i][x] == '#' && ++found)
    		new_asteroid(&(headsouth[i_head]), x, i);
    count += found ? 1 : 0;
    return (count);
}

// FIN PARTIE STOCKAGE


// DEBUT PARTIE TIRS DE LASER

// Quand on a detruit tous les lasers sur une vue, on detruit cette vue.
void    end_of_view(t_view **head, t_view *view)
{
    t_view  *prev;
    
    if (view == *head)
    {
        *head = view->next;
        return ;
    }
    prev = *head;
    while (prev->next != view)
    prev = prev->next;
    prev->next = view->next;
}

// Tir de laser sur un asteroide, ce qui l'enleve de sa liste chainee
// et stocke ses coordonnees dans x et y (pour le resultat final au cas ou c'est le dernier).
void    shoot(t_view **head, t_view *view, int *x, int *y)
{
    if (view->list)
    {
        *x = view->list->x;
        *y = view->list->y;
        //printf("shooting [%d][%d]\n", *y, *x);
        view->list = view->list->next;
        if (!view->list)
        	end_of_view(head, view);
    }
}

// Fonction principale de tirs de laser.
// Tire pile au nord,
// puis sur la face est (en tirant pile a l'est quand le ratio passe du positif au negatif),
// puis pile au sud,
// puis sur la face ouest (en tirant pile a l'ouest quand le ratio passe du positif au negatif).
void    pew_pew(int i_head)
{
    t_view  *view;
    int     count;
    int     x;
    int     y;
    
    count = 0;
    while ((headviews1[i_head] || headviews2[i_head]
    || headnorth[i_head] || headeast[i_head] || headsouth[i_head] || headwest[i_head])
    && count < LIMIT)
    {
        if (headnorth[i_head])
        {
            shoot(&(headnorth[i_head]), headnorth[i_head], &x, &y);
            count++;
            if (count == LIMIT)
            	break;
        }
        view = headviews1[i_head];
        if ((!view || view->ratio < 0) && headeast[i_head])
       {
            shoot(&(headeast[i_head]), headeast[i_head], &x, &y);
            count++;
            if (count == LIMIT)
            	break;
        }
        while (view)
        {
            shoot(&(headviews1[i_head]), view, &x, &y);
            count++;
            if (count == LIMIT)
            	break;
            if (view->ratio > 0 && (!view->next || view->next->ratio < 0) && headeast[i_head])
            {
                shoot(&(headeast[i_head]), headeast[i_head], &x, &y);
                count++;
                if (count == LIMIT)
                	break;
            }
            view = view->next;
        }
        if (count == LIMIT)
        	break;
        if (headsouth[i_head])
        {
            shoot(&(headsouth[i_head]), headsouth[i_head], &x, &y);
            count++;
            if (count == LIMIT)
            	break;
        }
        view = headviews2[i_head];
        if ((!view || view->ratio < 0) && headwest[i_head])
        {
            shoot(&(headwest[i_head]), headwest[i_head], &x, &y);
            count++;
            if (count == LIMIT)
            	break;
        }
        while (view)
        {
            shoot(&(headviews2[i_head]), view, &x, &y);
            count++;
            if (count == LIMIT)
            	break;
            if (view->ratio > 0 && (!view->next || view->next->ratio < 0) && headwest[i_head])
            {
                shoot(&(headwest[i_head]), headwest[i_head], &x, &y);
                count++;
                if (count == LIMIT)
                	break;
            }
            view = view->next;
        }
    }
    printf("Coordinates of the last (%dth) destroyed asteroid : %d\n", LIMIT, x * 100 + y);
}

// FIN PARTIE TIRS DE LASER

int		main(int ac, char **av)
    {
    char	*line;
    int		fd;
    int		y;
    int		x;
    int		views;
    int		max_views;
    int     i;
    int     max_i;
    
    if (ac != 2)
    	return (0);
    // Lecture de la carte
    fd = open(av[1], O_RDONLY);
    map_h = 0;
    while (get_next_line(fd, &line) == 1)
    	map[map_h++] = line;
    map_w = 0;
    while (map[0][map_w])
    	map_w++;
    // Stockage des informations, calcul de l'astéroïde de base
    max_views = 0;
    i = 0;
    y = -1;
    while (++y < map_h)
    {
        x = -1;
        while (++x < map_w)
        {
            if (map[y][x] == '#')
            {
                views = count_views(i, y, x);
                if (views > max_views)
                {
                    max_views = views;
                    max_i = i;
                }
                i++;
            }
        }
    }
    printf("max views = %d, max_i = %d\n", max_views, max_i);
    // Tirs !
    // max_i est la case a prendre dans les tableaux de 500 cases, pour tirer les lasers du bon asteroide
    pew_pew(max_i);
    return(0);
}

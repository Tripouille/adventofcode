#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int		get_next_line(int fd, char **line);

typedef struct				s_requirement
{
	long long				quantity;
	char					name[10];
}							t_requirement;

typedef struct				s_recipe
{
	long long				quantity;
	char					name[10];
	t_requirement			requirement[100];
}							t_recipe;

t_recipe			recipes[100];
t_requirement		stock[100];
long long			i_stock = 0;
long long			ore = 0;

/*
** Will set all the requirements for the current recipe,
** and set the stock of the recipe at 0.
*/

void	set_recipe(t_recipe *recipe, char *line)
{
	long long		i_requirement;
	long long		i;

	i_requirement = 0;
	while (*line != '>')
	{
		recipe->requirement[i_requirement].quantity = atoi(line);
		while (!isalpha(*line))
			line++;
		i = 0;
		while (isalpha(*line))
			recipe->requirement[i_requirement].name[i++] = *line++;
		recipe->requirement[i_requirement++].name[i] = 0;
		while (!isdigit(*line) && *line != '>')
			line++;
	}
	recipe->quantity = atoi(++line);
	while (!isalpha(*line))
		line++;
	strcpy(recipe->name, line);
	strcpy(stock[i_stock].name, line);
	stock[i_stock++].quantity = 0;
}

long long		get_from_stock(long long n, char *name) //Retire n au stock.
{
	long long		i_stock;

	i_stock = 0;
	while (strcmp(stock[i_stock].name, name))
		i_stock++;
	stock[i_stock].quantity -= n;
	return (stock[i_stock].quantity);
}

void	add_stock(long long n, char *name) //Ajoute n au stock.
{
	long long		i_stock;

	i_stock = 0;
	while (strcmp(stock[i_stock].name, name))
		i_stock++;
	stock[i_stock].quantity += n;
}

void	make(long long n, char *name) //Création de n resource.
{
	long long		i_recipe;
	long long		i_requirement;
	long long		in_stock;
	long long		required_cycle;

	i_recipe = -1;
	i_requirement = -1;
	while (strcmp(name, recipes[++i_recipe].name)); //On attrape la bonne recette.
	in_stock = get_from_stock(n, recipes[i_recipe].name); //On enléve le nécessaire.
	if (in_stock < 0) //On compense si besoin.
	{
		required_cycle = ((-in_stock / recipes[i_recipe].quantity) + ((-in_stock) % recipes[i_recipe].quantity ? 1 : 0));
		add_stock(required_cycle * recipes[i_recipe].quantity, recipes[i_recipe].name);
		if (!strcmp(recipes[i_recipe].requirement[0].name, "ORE")) //Si c'est une ressource de base.
			ore += required_cycle * recipes[i_recipe].requirement[0].quantity;
		else
			while (recipes[i_recipe].requirement[++i_requirement].quantity) //On make les dépendances.
				make(required_cycle * recipes[i_recipe].requirement[i_requirement].quantity,
					recipes[i_recipe].requirement[i_requirement].name);
	}
}

void	clear_stock()
{
	long long		i;

	i = -1;
	while (++i < i_stock)
		stock[i].quantity = 0;
}

int		main(int ac, char **av) //O.
{
	int					fd;
	char				*line;
	long long			i_recipe;
	long long			fuel;
	long long			first;
	const long long		limit = 1000000000000;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	i_recipe = 0;
	while (get_next_line(fd, &line) == 1)
		set_recipe(recipes + i_recipe++, line);
	ore = 0;
	make(1, "FUEL");
	fuel = 1;
	while (ore < limit)
	{
		fuel += (limit - ore) / (ore / fuel);
		ore = 0;
		clear_stock();
		make(fuel, "FUEL");
	}
	while (ore > limit)
	{
		fuel--;
		ore = 0;
		clear_stock();
		make(fuel, "FUEL");
	}
	printf("result = %lli\n", fuel);
	return(0);
}

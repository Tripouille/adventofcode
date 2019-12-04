/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   day4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jgambard <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/03 18:55:22 by jgambard     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/04 13:03:34 by jgambard    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		is_end(char *tab, char *end)
{
	int		i;

	i = 0;
	while (end[i])
	{
		if (tab[i] < end[i])
			return (0);
		else if (tab[i] > end[i])
			return (1);
		i++;
	}
	return (1);
}

int		is_valid(char *tab)
{
	int		double_crit;

	double_crit = 0;
	while (*tab)
	{
		if (tab[1] && tab[1] < *tab)
			return (0);
		if (tab[1] == *tab && tab[2] != *tab && tab[-1] != *tab)
			double_crit = 1;
		tab++;
	}
	return (double_crit);
}

int		main(void)
{
	char	tab[6] = "265275";
	int		valid_combs;
	int		i;

	valid_combs = 0;
	while (!is_end(tab, "781584"))
	{
		if (is_valid(tab))
			valid_combs++;
		i = 5;
		while (i && tab[i] == '9')
			i--;
		tab[i]++;
		while (i++ < 5)
			tab[i] = tab[i - 1];
	}
	printf("result = %i\n", valid_combs);
}

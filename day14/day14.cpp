/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day14.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:05:36 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/15 01:02:55 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "Chemical.hpp"
#include "Reaction.hpp"
using namespace std;

vector<Reaction> reactions;
vector<Chemical> stock;

void		printVector(vector<string>& vec)
{
	cerr << "print vec : " << endl;
	for (int i = 0; i< vec.size(); i++)
		cerr << vec[i] << " ";
	cerr << endl << "end print vec" << endl;
}

void		readReactions(void)
{
	ifstream		file("day14.txt");
	string			line;
	int				i;
	
	while (getline(file, line))
	{
		std::istringstream iss{line};
		vector<string> words
		{
			std::istream_iterator<string>(iss),
			std::istream_iterator<string>()
		};
		reactions.push_back(Reaction(Chemical(words.back(),
							std::stoi(words.at(words.size() - 2)))));
		while (words.front() != "=>")
		{
			if (words[1].back() == ',')
				words[1].erase(words[1].end() - 1);
			int quantity = std::stoi(words[0]);
			reactions.back().addComponent(Chemical(words[1], quantity));
			words.erase(words.begin(), words.begin() + 2);
		}
	}
}

Reaction&	getReaction(string outputName)
{
	int		size = reactions.size();
	for (int i = 0; i < size; i++)
		if (reactions[i].getOutput().getName() == outputName)
			return (reactions[i]);
	return (reactions[0]);
}

int			getNeededChemicalForStock(void)
{
	int		i_ore = 0;
	int		size = stock.size();
	for (int i = 0; i < size; i++)
		if (stock[i].getName() == "ORE")
			i_ore = i;
		else if (stock[i].getQuantity() < 0)
			return (i);
	return (i_ore);
}

int			getChemicalInStock(string name)
{
	int		size = stock.size();
	for (int i = 0; i < size; i++)
		if (stock[i].getName() == name)
			return (i);
	return (-1);
}

void		useReaction(Reaction& reaction, int i_output)
{
	vector<Chemical>& components = reaction.getComponents();
	int i_stock;
	long long quantityNeeded, outputQuantity, reactionNb;
	quantityNeeded = -stock[i_output].getQuantity();
	outputQuantity = reaction.getOutput().getQuantity();
	reactionNb = quantityNeeded / outputQuantity;
	if (quantityNeeded % outputQuantity)
		reactionNb++;
	for (int i = 0; i < components.size(); i++)
	{
		i_stock = getChemicalInStock(components[i].getName());
		if (i_stock == -1)
		{
			stock.push_back(Chemical(components[i].getName()));
			i_stock = stock.size() - 1;
		}
		Chemical &componentInStock = stock[i_stock];
		componentInStock.removeQuantity(reactionNb * components[i].getQuantity());
	}
	stock[i_output].addQuantity(reactionNb * outputQuantity);
}

bool		stockIsEmpty(void)
{
	int		size = stock.size();
	for (int i = 0; i < size; i++)
		if (stock[i].getQuantity() > 0)
			return (false);
	return (true);
}

int			main(void)
{
	readReactions();
	long long fuel = 0, ore = 0;
	stock.push_back(Chemical("FUEL"));
	while (ore <= 1000000000000)
	{
		//cerr << "fuel = " << fuel << ", ore = " << ore << endl;
		stock[0].removeQuantity(1);
		while (1)
		{
			int i = getNeededChemicalForStock();
			if (stock[i].getName() == "ORE")
			{
				ore = -stock[i].getQuantity();
				if (stockIsEmpty())
				{
					cout << "stock is empty at fuel = " << fuel << endl;
					return (0);
				}
				break ;
			}
			Reaction &reaction = getReaction(stock[i].getName());
			useReaction(reaction, i);
		}
		fuel++;
	}
	cout << "answer : " << fuel << endl;
	return (0);
}

/*int			main(void)
{
	readReactions();
	stock.push_back(Chemical("FUEL", -1));
	while (!stock.empty())
	{
		int i = getNeededChemicalForStock();
		if (stock[i].getName() == "ORE")
		{
			cout << "answer : " << -stock[i].getQuantity() << endl;
			return (0);
		}
		Reaction &reaction = getReaction(stock[i].getName());
		useReaction(reaction, i);
	}
	return (1);
}*/
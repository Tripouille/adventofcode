/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chemical.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:09:50 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/15 00:29:30 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Chemical.hpp"

Chemical::Chemical(std::string name_)
{
	name = name_;
	quantity = 0;
}

Chemical::Chemical(std::string name_, long long quantity_)
{
	name = name_;
	quantity = quantity_;
}

std::string		Chemical::getName() const
{
	return (name);
}

long long		Chemical::getQuantity() const
{
	return (quantity);
}

void			Chemical::addQuantity(long long n)
{
	quantity += n;
}

void			Chemical::removeQuantity(long long n)
{
	quantity -= n;
}
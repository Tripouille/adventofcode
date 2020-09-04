/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reaction.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:26:06 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/14 22:22:42 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Reaction.hpp"

Reaction::Reaction(Chemical output_) : output(output_) {}

void					Reaction::addComponent(Chemical component)
{
	components.push_back(component);
}

std::vector<Chemical>&	Reaction::getComponents()
{
	return (components);
}

Chemical&				Reaction::getOutput()
{
	return (output);
}
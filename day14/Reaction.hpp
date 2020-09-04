/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reaction.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 20:23:16 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/14 22:22:49 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef REACTION_H
# define REACTION_H

# include "Chemical.hpp"
# include <string>
# include <vector>

class Reaction
{
	private:
		std::vector<Chemical>	components;
		Chemical				output;
		
	public:
		Reaction(Chemical output_);
		void					addComponent(Chemical component);
		std::vector<Chemical>&	getComponents();
		Chemical&				getOutput();
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chemical.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalleman <aalleman@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:06:34 by aalleman          #+#    #+#             */
/*   Updated: 2020/05/15 00:29:40 by aalleman         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHEMICAL_H
# define CHEMICAL_H

# include <string>

class Chemical
{
	private:
		std::string		name;
		long long			quantity;
		
	public:
		Chemical(std::string name_);
		Chemical(std::string name_, long long quantity_);
		std::string		getName() const;
		long long		getQuantity() const;
		void			addQuantity(long long n);
		void			removeQuantity(long long n);
};

#endif
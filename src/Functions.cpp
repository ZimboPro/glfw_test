/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functions.cpp                                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-jage   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 12/47/59 by lde-jage          #+#    #+#             */
/*   Updated: 2018/07/11 12/47/59 by lde-jage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Functions.hpp"

Functions::Functions() {}

Functions::Functions(Functions const & src) {
	*this = src;	
}

Functions::~Functions() {}

Functions & Functions::operator=(Functions const & src) {
	if (this != &src)
    {
	*this = src;
    }
	return (*this);
}

void Functions::Loop()
{
	std::cout << "test" << std::endl;
}

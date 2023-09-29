/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:17:10 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/27 18:30:23 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

//---------------------- Constructors & Destructors ----------------------

Message::Message() : raw(""), cmd("")
{}

Message::Message(const Message& toCopy)
{
	*this = toCopy;
}

Message::~Message()
{}

//------------------------- Operators Overloads --------------------------

Message&	Message::operator=(const Message& rhs)
{
	raw = rhs.raw;
	cmd = rhs.cmd;
	args = rhs.args;
	return (*this);
}

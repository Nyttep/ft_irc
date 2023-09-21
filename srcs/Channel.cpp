/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:32:23 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/21 14:32:23 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

//---------------------- Constructors & Destructors ----------------------

Channel::Channel()
{}

Channel::Channel(std::string newName) : _name(newName)
{}

Channel::Channel(const Channel& toCopy)
{
	*this = toCopy;
}

Channel::~Channel()
{}

//------------------------- Operators Overloads --------------------------

Channel&	Channel::operator=(const Channel& rhs)
{
	_name = rhs._name;
	_users = rhs._users;
	return (*this);
}

// ------------------------- Setters & Getters ---------------------------

std::string	Channel::getName()
{
	return (_name);
}

User&	Channel::getUser(int key)
{
	User&	ret = _users.find(key);
	if (ret == _users.end())
		return (NULL);
	return (ret);
}

bool	Channel::addUser(int key, User value)
{
	if (this->isRegistered(key))
		return (0);
	std::pair<std::map<int, User>::iterator, bool>	ret = _users.insert(std::pair<int, User>(key, value));
	return (ret.second);
}

//--------------------------- Other Functions ----------------------------

bool	Channel::isInChannel(int key)
{
	return (_users.count(key));
}

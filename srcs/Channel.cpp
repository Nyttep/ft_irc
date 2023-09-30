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

#include "irc.hpp"

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
	std::map<int, User>::iterator	found = _users.find(key);
	User&	ret = found->second;
	return (ret);
}

bool	Channel::addUser(int key, User value)
{
	if (this->isInChannel(key))
		return (0);
	std::pair<std::map<int, User>::iterator, bool>	ret = _users.insert(std::pair<int, User>(key, value));
	return (ret.second);
}

void	Channel::addInvite(User client)
{
	_invite.push_back(client);
}

//--------------------------- Other Functions ----------------------------

bool	Channel::isInChannel(int key)
{
	return (_users.count(key));
}

bool	Channel::isOperator(User client)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (client.getNName() == _operators[i].getNName())
			return true;
	}
		return false;
}
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

void	Channel::addOperator(User client)
{
	_operators.push_back(client);
}

void	Channel::removeOperator(User client)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (_operators[i].getNName() == client.getNName())
		{
			_operators.erase(_operators.begin() + i);
			return ;
		}
	}
}

void	Channel::addInvite(User client)
{
	_invite.push_back(client);
}

void	Channel::removeInvite(User client)
{
	for (size_t i = 0; i != _invite.size(); ++i)
	{
		if (_invite[i].getNName() ==  client.getNName())
		{
			_invite.erase(_invite.begin() + i);
			return ;
		}
	}
}

void	Channel::setKey(std::string key)
{
	_key = key;
}

std::string	Channel::getKey()
{
	return (_key);
}

void	Channel::setTopic(std::string topic)
{
	_topic = topic;
}

std::string	Channel::getTopic()
{
	return (_topic);
}

void	Channel::setLimit(size_t limit)
{
	_limit = limit;
}

size_t	Channel::getLimit()
{
	return (_limit);
}

void	Channel::setI(bool value)
{
	_i = value;
}

bool	Channel::getI()
{
	return (_i);
}

void	Channel::setT(bool value)
{
	_t = value;
}

bool	Channel::getT()
{
	return (_t);
}

void	Channel::setK(bool value)
{
	_k = value;
}

bool	Channel::getK()
{
	return (_k);
}

void	Channel::setL(bool value)
{
	_l = value;
}

bool	Channel::getL()
{
	return (_l);
}

//--------------------------- Other Functions ----------------------------

bool	Channel::isInChannel(int key)
{
	return (_users.count(key));
}

bool	Channel::onChannel(User client)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (client.getNName() == _operators[i].getNName())
			return (true);
	}
	for (size_t i = 0; i != _users.size(); ++i)
	{
		if (client.getNName() == _users[i].getNName())
			return (true);
	}
	return (false);
}

bool	Channel::isOperator(User client)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (client.getNName() == _operators[i].getNName())
			return (true);
	}
	return (false);
}

bool	Channel::isInvite(User client)
{
	for (size_t i = 0; i != _invite.size(); ++i)
	{
		if (client.getNName() == _invite[i].getNName())
			return (true);
	}
	return (false);
}

bool	Channel::maxUser()
{
	if ((_operators.size() + _users.size() + 1) > _limit)
		return (true);
	return (false);
}
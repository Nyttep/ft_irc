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

User*	Channel::getUser(std::string nick)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (nick == _operators[i]->getNName())
			return (_operators[i]);
	}
	for (size_t i = 0; i != _users.size(); ++i)
	{
		if (nick == _users[i]->getNName())
			return (_users[i]);
	}
	return (NULL);
}

void	Channel::addUser(User* value)
{
	if (this->onChannel(value->getNName()))
		return ;
	_users.push_back(value);
}

void	Channel::addOperator(User *client)
{
	_operators.push_back(client);
}

void	Channel::removeOperator(User client)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (_operators[i]->getNName() == client.getNName())
		{
			_operators.erase(_operators.begin() + i);
			return ;
		}
	}
}

void	Channel::addInvite(User *client)
{
	_invite.push_back(client);
}

void	Channel::removeInvite(User client)
{
	for (size_t i = 0; i != _invite.size(); ++i)
	{
		if (_invite[i]->getNName() ==  client.getNName())
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

bool	Channel::onChannel(std::string nick)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (nick == _operators[i]->getNName())
			return (true);
	}
	for (size_t i = 0; i != _users.size(); ++i)
	{
		if (nick == _users[i]->getNName())
			return (true);
	}
	return (false);
}

bool	Channel::isOperator(User client)
{
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		if (client.getNName() == _operators[i]->getNName())
			return (true);
	}
	return (false);
}

bool	Channel::isInvite(User client)
{
	for (size_t i = 0; i != _invite.size(); ++i)
	{
		if (client.getNName() == _invite[i]->getNName())
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

size_t Channel::nbUser()
{
	return (_operators.size() + _users.size())
}

void	Channel::sendToChan(std::string message, std::string prefix)
{
	for (size_t i = 0; i != _operators.size(); ++i)
		sendAll(message, _operators[i]);
	if (prefix.empty())
	{	
		for (size_t i = 0; i != _users.size(); ++i)
			sendAll(message, _users[i]);
	}
}

void	Channel::sendUsersList(User &user)
{
	std::string userlist;
	for (size_t i = 0; i != _operators.size(); ++i)
	{
		userlist = "@" + _operators[i].getNName();
		sendAll(RPL_NAMEREPLY(user.getNName(), _name, userlist), user);
	}
	for (size_t i = 0; i != _users.size(); ++i)
	{
		sendAll(RPL_NAMEREPLY(user.getNName(), _name, _users[i].getNName()), user);
	}
	sendAll(RPL_ENDOFNAMES(user.getNName(), _name), user);
}
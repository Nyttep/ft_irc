/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:56:41 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/20 19:56:41 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

//---------------------- Constructors & Destructors ----------------------

Server::Server()
{}

Server::Server(std::string newPswd, std::string newPort) : _pswd(newPswd), _port(newPort)
{}

Server::Server(const Server& toCopy)
{
	*this = toCopy;
}

Server::~Server()
{
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); it++)
		delete it->second;
	for (std::vector<Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
		delete *it;
}

//----------------------- Operators Overloads ---------------------------

Server&	Server::operator=(const Server& rhs)
{
	_pswd = rhs._pswd;
	_port = rhs._port;
	_users = rhs._users;
	return (*this);
}

// ------------- Setters & Getters ---------------------

std::string	Server::getPswd()
{
	return (_pswd);
}

std::string	Server::getPort()
{
	return (_port);
}

User&	Server::getUser(int key)
{
	std::map<int, User*>::iterator	found = _users.find(key);
	User&	ret = *found->second;
	return (ret);
}
  
//------------------------- Other Functions -----------------------------

bool	Server::addUser(int key, User *value)
{
	std::pair<std::map<int, User*>::iterator, bool>	ret = _users.insert(std::pair<int, User*>(key, value));
	return (ret.second);
}

bool	Server::removeUser(int key)
{
	delete _users.find(key)->second;
	return (_users.erase(key));
}

void	Server::addChan(Channel	*newChan)
{
	_channels.push_back(newChan);
}

bool	Server::isValidPswd(std::string tryPswd)
{
	if (tryPswd == _pswd)
		return (true);
	return (false);
}

bool	Server::isRegistered(int key)
{
	return (_users.count(key));
}
 
bool	Server::chanExist(std::string name)
{
	if (_channels.empty())
		return (false);
	for (std::vector<Channel*>::iterator	it = _channels.begin(); it != _channels.end(); it++)
	{
		if (name == it->getName())
			return (true);
	}
	return (false);
}

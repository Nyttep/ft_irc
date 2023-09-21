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

#include "Server.hpp"

//---------------------- Constructors & Destructors ----------------------

Server::Server()
{}

Server::Server(std::string newPswd, int newPort) : _pswd(newPswd), _port(newPort)
{}

Server::Server(const Server& toCopy)
{
	*this = toCopy;
}

Server::~Server()
{}

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

int	Server::getPort()
{
	return (_port);
}

User&	Server::getUser(int key)
{
	User&	ret = _users.find(key);
	if (ret == _users.end())
		return (NULL);
	return (ret);
}
  
bool	Server::addUser(int key, User value)
{
	if (this->isRegistered(key))
		return (0);
	std::pair<std::map<int, User>::iterator, bool>	ret = _users.insert(std::pair<int, User>(key, value));
	return (ret.second);
}

void	Server::addChan(Channel	newChan)
{
	_channels.push_back(newChan);
}

//------------------------- Other Functions -----------------------------

bool	Server::isValidPswd(std::string try)
{
	if (try == _pswd)
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
	for (std::vector<Channel>::iterator	it = _channels.begin(); it++; it != _channels.end())
	{
		if (name == it->getName())
			return (true);
	}
	return (false);
}

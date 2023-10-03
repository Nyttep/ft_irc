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
{
	_setTime();
}

Server::Server(std::string newPswd, std::string newPort) : _pswd(newPswd), _port(newPort)
{
	_setTime();
}

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

User*	Server::getUser(int key)
{
	std::map<int, User*>::iterator	found = _users.find(key);
	if (found == _users.end())
		return (NULL);
	return (found->second);
}

User*	Server::getUser(std::string name)
{
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (name == it->second->getNName())
			return (it->second);
	}
	return (NULL);
}

Channel*	Server::getChan(std::string name)
{
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (name == (*it)->getName())
			return (*it);
	}
	return (NULL);
}

std::string	Server::getTime()
{
	return (_time);
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

bool	Server::isUser(std::string name)
{
	for (std::map<int, User*>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		if (name == it->second->getNName())
			return (true);
	}
	return (false);
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
		if (name == (*it)->getName())
			return (true);
	}
	return (false);
}

bool	Server::nicknameCollision(std::string nickname)
{
	std::string low_nick;
	for(std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		low_nick = it->second->getNName();
		for (size_t i = 0; i != low_nick.length(); ++i)
			low_nick[i] = std::tolower(low_nick[i]);
		if (nickname == low_nick)
			return (true);
	}
	return (false);
}

void		Server::allUsersMessage(std::string message)
{
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		sendAll(message, *it->second);
	}
}

void	Server::_setTime()
{
	std::string str;
    std::stringstream stream;
	std::time_t time = std::time(NULL);

	std::tm *tm = std::localtime(&time);
    stream << tm->tm_hour << ":" << tm->tm_min << " " << tm->tm_mday << "/" << 1 + tm->tm_mon << "/" << tm->tm_year - 100;
    str += stream.str();
    this->_time = str;
}

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

Server::Server(std::string newPswd, std::string newPort) : _pswd(newPswd), _port(newPort), _fdCount(0)
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

std::vector<struct pollfd>&	Server::getPfds()
{
	return (_pfds);
}

int&	Server::getFDCount()
{
	return (_fdCount);
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

void	Server::removeChan(std::string name)
{
	for (size_t i = 0; _channels.size(); ++i)
	{
		if (name == _channels[i]->getName())
		{
			delete _channels[i];
			_channels.erase(_channels.begin() + i);
			return ;
		}
	}
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

void	Server::allUsersMessage(std::string message)
{
	for (std::map<int, User *>::iterator it = _users.begin(); it != _users.end(); ++it)
	{
		sendAll(message, *it->second);
	}
}

std::string	Server::setMinute(int minutes)
{
	std::stringstream	stream;
	if (minutes < 10)
		stream << "0" << minutes;
	else
		stream << minutes;
	return (stream.str());
}

void	Server::_setTime()
{
	std::string str;
    std::stringstream stream;
	std::time_t time = std::time(NULL);

	std::tm *tm = std::localtime(&time);
    stream << tm->tm_mday << "/" << 1 + tm->tm_mon << "/" << tm->tm_year - 100 << " at " << tm->tm_hour << ":" << setMinute(tm->tm_min);
    str += stream.str();
    this->_time = str;
}

void	Server::initPfds(int listener)
{
	struct pollfd				listenerStruct;

	std::memset(&listenerStruct, 0, sizeof(listenerStruct));
	_pfds.push_back(listenerStruct);
	_pfds[0].fd = listener;
	_pfds[0].events = POLLIN;
	_fdCount++;
}

void	Server::delFromPfds(int fd)
{
	for (std::vector<struct pollfd>::iterator it = _pfds.begin(); it != _pfds.end(); it++)
	{
		if (it->fd == fd)
		{
			_pfds.erase(it);
			_fdCount--;
			return ;
		}
	}
}

void	Server::disconnectUser(int fd)
{
	_users.find(fd)->second->leaveAllChan(*this);
	close(fd);
	delFromPfds(fd);
	removeUser(fd);
}

void	Server::listInvite(Command &command)
{
	if (!_channels.empty())
	{
		for (size_t i = 0; i != _channels.size(); ++i)
		{
			if (_channels[i]->isInvite(command.getSource()) == true)
			{
				sendAll(RPL_INVITELIST(HOSTNAME, command.getSource()->getNName(), _channels[i]->getName()), *command.getSource());
			}
		}
	}
	sendAll(RPL_ENDOFINVITELIST(HOSTNAME, command.getSource()->getNName()), *command.getSource());
}

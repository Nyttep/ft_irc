/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:33:48 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/21 14:33:48 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

//---------------------- Constructors & Destructors ----------------------

User::User()
{
}

User::User(int newFD) : _fd(newFD), _nName(""), _uName(""), _rName(""), _pass(false), _registered(false)
{
}

User::User(const User& toCopy)
{
	*this = toCopy;
}

User::~User()
{}

//------------------------- Operators Overloads --------------------------

User&	User::operator=(const User& rhs)
{
	_nName = rhs._nName;
	_uName = rhs._uName;
	_rName = rhs._rName;
	_fd = rhs._fd;
	_port = rhs._port;
	_lChannel = rhs._lChannel;
	_gChannel = rhs._gChannel;
	_pass = rhs._registered;
	_msg = rhs._msg;
	_extra = rhs._extra;
	return (*this);
}

// ------------------------- Setters & Getters ---------------------------

std::string	User::getNName()
{
	return (_nName);
}

void		User::setNName(std::string newNName)
{
	_nName = newNName;
}

std::string	User::getUName()
{
	return (_uName);
}

void		User::setUName(std::string newUName)
{
	_uName = newUName;
}

std::string	User::getRName()
{
	return (_rName);
}

void		User::setRName(std::string newRName)
{
	_rName = newRName;
}

std::string	User::getMsg()
{
	return (_msg);
}

bool	User::getPass()
{
	return (_pass);
}

void	User::setPass(bool value)
{
	_pass = value;
}

bool	User::getRegistered()
{
	return (_registered);
}

void	User::setRegistered(bool value)
{
	_registered = value;
}

int	User::getFD()
{
	return (_fd);
}

void	User::setHName(std::string newHName)
{
	_hName = newHName;
}

std::string	User::getHName()
{
	return (_hName);
}

//--------------------------- Other Functions ----------------------------

void	User::clearMsg()
{
	_msg.clear();
}

bool	User::formatRecvData(std::vector<char>& buff)
{
	std::string				tmp(buff.data());

	if (!_extra.empty())
	{
		tmp.append(_extra);
		_extra.clear();
	}

	std::string::size_type	pos = tmp.find("\r\n");

	if (pos == std::string::npos)
	{
		_msg.append(tmp);
		return (EOT_NOT_FOUND);
	}
	_msg.append(tmp.substr(0, pos + 2));
	_extra = tmp.substr(pos + 2, tmp.size());
	if (!_extra.empty())
		return (FOUND_EXTRA);
	return (EOT);
}

bool	User::maxChannel(std::string channel)
{
	if (channel[0] == '#')
	{
		if ((_gChannel.size() + 1) > chanlimit(channel[0]))
			return (true);
		else
			return (false);
	}
	else if (channel[0] == '&')
	{
		if ((_lChannel.size() + 1) > chanlimit(channel[0]))
			return (true);
		else
			return (false);
	}
	else
		return (true);
}
  
void	User::joinChan(Channel* chan)
{
	if (chan->getName()[0] == '&')
		_lChannel.push_back(chan);
	else
		_gChannel.push_back(chan);
}

void	User::leaveAllChanPART(Command &command, Server &server)
{
	std::string message;
	if ((command.getParams().size() >= 2) && (!command.getParams()[1].empty()))
		message = std::string(" :") + command.getParams()[1];
	else
		message = " :Left the channel";
	while (!_lChannel.empty())
	{
		std::string channel = _lChannel[0]->getName();
		_lChannel[0]->sendToChan(US_PART(setUserAddress(*this), _lChannel[0]->getName(), message), "", "");
		if (_lChannel[0]->isOperator(this) == true)
			_lChannel[0]->removeOperator(this);
		else
			_lChannel[0]->removeUser(this);
		if (server.getChan(channel)->nbUser() == 0)
		server.removeChan(channel);
	}
	while (!_gChannel.empty())
	{
		std::string channel = _gChannel[0]->getName();
		_gChannel[0]->sendToChan(US_PART(setUserAddress(*this), _gChannel[0]->getName(), message), "", "");
		if (_gChannel[0]->isOperator(this) == true)
			_gChannel[0]->removeOperator(this);
		else
			_gChannel[0]->removeUser(this);
		if (server.getChan(channel)->nbUser() == 0)
			server.removeChan(channel);
	}
}

void	User::quitChan(Channel& chan)
{
	for (std::vector<Channel*>::iterator it = _lChannel.begin(); it != _lChannel.end(); it++)
	{
		if ((*it)->getName() == chan.getName())
		{
			_lChannel.erase(it);
			return ;
		}
	}
	for (std::vector<Channel*>::iterator it = _gChannel.begin(); it != _gChannel.end(); it++)
	{
		if ((*it)->getName() == chan.getName())
		{
			_gChannel.erase(it);
			return ;
		}
	}
}

void	User::sendToAllChan(std::string	message)
{
	for (size_t i = 0; i != _lChannel.size(); ++i)
	{
		_lChannel[i]->sendToChan(message, "", _nName);
	}
	for (size_t i = 0; i != _gChannel.size(); ++i)
	{
		_gChannel[i]->sendToChan(message, "", _nName);
	}
}

void	User::leaveAllChan(Server &server)
{
	while (!_lChannel.empty())
	{
		std::string channel = _lChannel[0]->getName();
		if (_lChannel[0]->isOperator(this) == true)
			_lChannel[0]->removeOperator(this);
		else
			_lChannel[0]->removeUser(this);
		if (server.getChan(channel)->nbUser() == 0)
			server.removeChan(channel);
	}
	while (!_gChannel.empty())
	{
		std::string channel = _gChannel[0]->getName();
		if (_gChannel[0]->isOperator(this) == true)
			_gChannel[0]->removeOperator(this);
		else
			_gChannel[0]->removeUser(this);
		if (server.getChan(channel)->nbUser() == 0)
			server.removeChan(channel);
	}
}

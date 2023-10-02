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

//--------------------------- Other Functions ----------------------------

void	User::clearMsg()
{
	_msg.clear();
}

bool	User::formatRecvData(std::vector<char>& buff)
{
	std::string				tmp(buff.data());
	std::string::size_type	pos = tmp.find("\r\n");

	if (!_extra.empty())
	{
		_msg.append(_extra);
		_extra.clear();
	}
	if (pos == std::string::npos)
	{
		_msg.append(tmp);
		return (0);
	}
	_msg.append(tmp.substr(0, pos + 2));
	_extra.append(tmp.substr(pos + 2, tmp.size()));
	return (1);
}

bool	User::maxChannel(std::string channel)
{
	if (channel[0] == '#')
	{
		if ((_gChannel.size() + 1) > chanlimit(channel))
			return (true);
		else
			return (false);
	}
	else if (channel[0] == '&')
	{
		if ((_lChannel.size() + 1) > chanlimit(channel))
			return (true);
		else
			return (false);
	}
	else
		return (true);
}
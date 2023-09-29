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

User::User() : _nName(""), _uName(""), _rName(""), _isLogged(false), _fd(0)
{
}

User::User(int newFD) : _fd(newFD) , _isLogged(false)
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
	_isLogged = rhs._isLogged;
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

Message	User::getMsg()
{
	return (_msg);
}

int	User::getFD()
{
	return (_fd);
}

//--------------------------- Other Functions ----------------------------

bool	User::isLogged()
{
	return (_isLogged);
}

void	User::logIn()
{
	_isLogged = true;
}

void	User::logOut()
{
	_isLogged = false;
}

void	User::clearMsg()
{
	_msg.raw.clear();
	_msg.cmd.clear();
	_msg.args.clear();
}

bool	User::formatRecvData(std::vector<char>& buff)
{
	std::string				tmp(buff.data());
	std::string::size_type	pos = tmp.find("\r\n");

	if (!_extra.empty())
	{
		_msg.raw.append(_extra);
		_extra.clear();
	}
	if (pos == std::string::npos)
	{
		_msg.raw.append(tmp);
		return (0);
	}
	_msg.raw.append(tmp.substr(0, pos + 2));
	_extra.append(tmp.substr(pos + 2, tmp.size()));
	return (1);
}

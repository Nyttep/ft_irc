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

#include "User.hpp"

//---------------------- Constructors & Destructors ----------------------

User::User() : _nName(""), _uName(""), _rName(""), _isOP(false)
{}

User::User(std::string newNName, std::string newUName) : _nName(newNName), _uName(newUName), _rName(""), _isOP(false)
{}

User::User(std::string newNName, std::string newUName, std::string newRName) : _nName(newNName), _uName(newUName), _rName(newRName), _isOP(false)
{}

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
	_isOP = rhs._isOP;
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

void		User::setUName(std::string newUName);
{
	_uName = newUName;
}

std::string	User::getRName()
{
	return (_rName);
}

void		User::setRName(std::string newRName);
{
	_rName = newRName;
}

bool		User::isOP()
{
	return (_isOP);
}

void	User::makeOP()
{
	_isOP = true;
}

void	User::removeOP()
{
	_isOP = false;
}

//--------------------------- Other Functions ----------------------------


bool		User::isOP()
{
	return (_isOP);
}

void	User::makeOP()
{
	_isOP = true;
}

void	User::removeOP()
{
	_isOP = false;
}

//--------------------------- Other Functions ----------------------------


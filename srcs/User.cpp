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

void	User::leaveAllChan(Command command, Server server)
{
	std::string	message_user;
	std::string message_chan;
	std::string nick;
	while (!_lChannel.empty())
	{
		if (_lChannel[0].isOperator(*this) == true)
			nick = "@" + command.getSource().getNName();
		std::string message_channel = ":" + SERVERNAME + " " + nick + " " + channels[i] " :User has left the channel";
		std::string message_user = ":" + SERVERNAME + " " + nick + " " + channels[i] " :You have left the channel";
		if (command.getParams().size() > 1)
		{
			message_channel += " :";
			message_user += " :"
			for (size_t j = 1; j != command.getParams().size(); ++j)
			{
				if (!command.getParams()[j].empty())
				{
					message_channel += " " + command.getParams()[j];
					message_user += " " + command.getParams()[j];
				}
			}
		}
		message_channel += "\r\n";
		message_user += "\r\n";
		if (_lChannel[0].isOperator(*this) == true)
			_lChannel[0].removeOperator(*this);
		else
			_lChannel[0].removeUser(*this);
		sendAll(message_user, *this);
		_lChannel[0].sendToChan(message_channel, "");
		_lChannel.erase(_lChannel.begin());
	}
	while (!_gChannel.empty())
	{
		if (_gChannel[0].isOperator(*this) == true)
			nick = "@" + command.getSource().getNName();
		else
			nick = command.getSource().getNName();
		std::string message_channel = ":" + SERVERNAME + " " + nick + " " + channels[i] " :User has left the channel";
		std::string message_user = ":" + SERVERNAME + " " + nick + " " + channels[i] " :You have left the channel";
		if (command.getParams().size() > 1)
		{
			message_channel += " :";
			message_user += " :"
			for (size_t j = 1; j != command.getParams().size(); ++j)
			{
				if (!command.getParams()[j].empty())
				{
					message_channel += " " + command.getParams()[j];
					message_user += " " + command.getParams()[j];
				}
			}
		}
		message_channel += "\r\n";
		message_user += "\r\n";
		if (_gChannel[0].isOperator(*this) == true)
			_gChannel[0].removeOperator(*this);
		else
			_gChannel[0].removeUser(*this);
		sendAll(message_user, *this);
		_gChannel[0].sendToChan(message_channel, "");
		_gChannel.erase(_gChannel.begin());
	}
}
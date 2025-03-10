/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:45 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:42:02 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_NICK(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		if (command.getSource()->getNName().empty())
		{
			sendAll(ERR_NONICKNAMEGIVEN(HOSTNAME, "*"), *command.getSource());
		}
		else
		{
			sendAll(ERR_NONICKNAMEGIVEN(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		}
		return ;
	}
	if (correct_nick(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	
	if (command.getParams()[0].length() > NICKLEN)
		command.setPParams(0, command.getParams()[0].erase(NICKLEN, command.getParams()[0].length() - NICKLEN));
	std::string	low_nick = command.getParams()[0];
	for (size_t i = 0; i != low_nick.length(); ++i)
		low_nick[i] = std::tolower(low_nick[i]);
	if (server.nicknameCollision(low_nick) == true)
	{
		if (command.getSource()->getNName().empty())
		{
			sendAll(ERR_NICKNAMEINUSE(HOSTNAME, "*", command.getParams()[0]), *command.getSource());
		}
		else
		{
			sendAll(ERR_NICKNAMEINUSE(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		}
		return ;
	}
	if (command.getSource()->getRegistered() == true)
	{
		std::string formername = command.getSource()->getNName();
		command.getSource()->setNName(command.getParams()[0]);
		server.allUsersMessage(US_NICK(formername, command.getSource()->getNName()));
	}
	else if (command.getSource()->getUName().empty() && command.getSource()->getRName().empty() && command.getSource()->getHName().empty())
	{
		command.getSource()->setNName(command.getParams()[0]);
		return ;
	}
	else
	{
		command.getSource()->setRegistered(true);
		command.getSource()->setNName(command.getParams()[0]);
		handshake(command, server);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:45 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 10:52:01 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_NICK(Command &command, Server &server) /* prendre le serveur en paramètres */
{
		// Empty vector
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		if (command.getSource()->getNName().empty())
			sendAll(ERR_NONICKNAMEGIVEN("guest", command.getSource()->getNName()), *command.getSource());
		else
			sendAll(ERR_NONICKNAMEGIVEN(setUserAddress(*command.getSource()), command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 431" << std::endl;
		return ;
	}
	// Invalid character
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	
	if (command.getParams()[0].length() > NICKLEN)
		command.setPParams(0, command.getParams()[0].erase(NICKLEN, command.getParams()[0].length() - NICKLEN));
	std::string	low_nick = command.getParams()[0];
	std::cout << low_nick << std::endl;
	for (size_t i = 0; i != low_nick.length(); ++i)
		low_nick[i] = std::tolower(low_nick[i]);
	std::cout << low_nick << std::endl;
	if (server.nicknameCollision(low_nick) == true)
	{
		if (command.getSource()->getNName().empty())
			sendAll(ERR_NICKNAMEINUSE("guest", command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		else
			sendAll(ERR_NICKNAMEINUSE(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 433" << std::endl;
		return ;
	}
	if (command.getSource()->getRegistered() == true)
	{
		std::string formername = command.getSource()->getNName();
		command.getSource()->setNName(command.getParams()[0]);
		std::string message = std::string(":") + SERVERNAME + " :" + formername + " changed his nickname to " + command.getSource()->getNName() + "\r\n";
		server.allUsersMessage(message);
	}
	else if (command.getSource()->getUName().empty() && command.getSource()->getRName().empty())
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
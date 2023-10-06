/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:32 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:41:56 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_KICK(Command &command, Server &server, std::vector<std::string> targets, size_t i)
{
	if (correct_nick(targets[i]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
		return ;
	}
	if (server.isUser(targets[i]) == false)
	{
		sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(server.getUser(targets[i])) == false)
	{
		sendAll(ERR_USERNOTINCHANNEL(HOSTNAME, command.getSource()->getNName(), targets[i], command.getParams()[0]), *command.getSource());
		return ;
	}
	if (command.getParams().size() == 2)
	{
		server.getChan(command.getParams()[0])->sendToChan(US_KICK(setUserAddress(*command.getSource()), command.getParams()[0], targets[i], ""), "", "");
	}
	else
	{
		std::string message;
		if (!command.getParams()[2].empty())
		{
			message = std::string(" :") + command.getParams()[2];
			if (message.size() > KICKLEN + 2)
				message.erase(KICKLEN + 2, message.length() - (KICKLEN + 2));
		}
		server.getChan(command.getParams()[0])->sendToChan(US_KICK(setUserAddress(*command.getSource()), command.getParams()[0], targets[i], message), "", "");
	}
	if (server.getChan(command.getParams()[0])->isOperator(server.getUser(targets[i])) == true)
		server.getChan(command.getParams()[0])->removeOperator(server.getUser(targets[i]));	
	else
		server.getChan(command.getParams()[0])->removeUser(server.getUser(targets[i]));
}

void	execute_KICK(Command& command, Server& server)
{
	if (command.getParams().empty() || command.getParams().size() < 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (correct_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	std::vector<std::string>	targets = collect_arguments(command.getParams()[1]);
	for (size_t i = 0; i != targets.size() && i < targmax(command.getVerb()); ++i)
	{
		multiple_KICK(command, server, targets, i);
	}
}
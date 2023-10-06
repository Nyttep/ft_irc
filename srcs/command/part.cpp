/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:48 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:31:12 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PART(Command &command, Server &server, std::vector<std::string> channels, size_t i)
{
	if (channels[i].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (chantypes(channels[i][0]) == true && correct_chan(channels[i]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, channels[i]), *command.getSource());
		return ;
	}
	if (server.chanExist(channels[i]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.getChan(channels[i])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	std::string	message;
	if (command.getParams().size() > 1)
		message = std::string(" :") + command.getParams()[1];
	server.getChan(channels[i])->sendToChan(US_PART(setUserAddress(*command.getSource()), channels[i], message), "", "");
	if (server.getChan(channels[i])->isOperator(command.getSource()) == true)
		server.getChan(channels[i])->removeOperator(command.getSource());
	else
		server.getChan(channels[i])->removeUser(command.getSource());
	if (server.getChan(channels[i])->nbUser() == 0)
		server.removeChan(channels[i]);
}

void	execute_PART(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	std::vector<std::string>	channels = collect_arguments(command.getParams()[0]);
	if (channels.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		return ;
	}
	for (size_t i = 0; i != channels.size(); ++i)
	{
		multiple_PART(command, server, channels, i);
	}
}
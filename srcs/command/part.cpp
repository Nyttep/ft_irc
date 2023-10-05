/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:48 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 18:48:23 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PART(Command &command, Server &server, std::vector<std::string> channels, size_t i)
{
	if (channels[i].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cout << "Redirection 461" << std::endl;
		return ;
	}
	if (chantypes(channels[i][0]) == true && correct_chan(channels[i]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, channels[i]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(channels[i]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
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
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	std::vector<std::string>	channels = collect_arguments(command.getParams()[0]);
	if (channels.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	for (size_t i = 0; i != channels.size(); ++i)
	{
		multiple_PART(command, server, channels, i);
	}
}
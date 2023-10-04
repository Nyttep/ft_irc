/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:48 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 19:16:49 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PART(Command &command, Server &server, std::vector<std::string> channels, size_t i)
{
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), channels[i]), *command.getSource());
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
	if (server.getChan(channels[i])->isOperator(command.getSource()) == true)
		server.getChan(channels[i])->removeOperator(command.getSource());
	else
		server.getChan(channels[i])->removeUser(command.getSource());
	server.getChan(channels[i])->sendToChan(US_PART(setUserAddress(*command.getSource()), channels[i], message), "", "");
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
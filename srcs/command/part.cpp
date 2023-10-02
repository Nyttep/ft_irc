/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:48 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 18:33:45 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PART(Command &command, Server &server, std::vector<std::string> channels, size_t i)
{
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), channels[i]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(channels[i]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0]->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	std::string	nick;
	if (server.getChan(channels[i])->isOperator(command.getSource()) == true)
		nick = "@" + command.getSource()->getNName();
	else
		nick = command.getSource()->getNName();
	std::string message_channel = ":" + SERVERNAME + " " + nick + " " + channels[i] " :User has left the channel";
	std::string message_user = ":" + SERVERNAME + " " + nick + " " + channels[i] " :You have left the channel";
	if (command.getParams().size() > 1)
	{
		message_channel += " :";
		message_user += " :";
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
	if (server.getChan(channels[i]).isOperator(command.getSource(), server.getChan(channels[i])) == true)
		server.getChan(channels[i]).removeOperator(command.getSource());
	else
		server.getChan(channels[i]).removeUser(command.getSource());
	sendAll(message_user, command.getSource());
	server.getChan(channels[i]).sendToChan(message_channel);
	std::cout << message_channel << std::endl;
	std::cout << message_user << std::endl;
}

void	execute_PART(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	std::vector<std::string>	channels = collect_arguments(command.getParams()[0]);
	if (channels.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	for (size_t i = 0; i != channels.size(); ++i)
	{
		multiple_PART(command, server, channels, i);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:32 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/03 15:03:47 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_KICK(Command &command, Server &server, std::vector<std::string> targets, size_t i)
{
	if (correct_nick_chan(targets[i]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), targets[i]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.isUser(targets[i]) == false)
	{
		sendAll(ERR_NOSUCHNICK(command.getSource()->getNName(), targets[i]), *command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(server.getUser(targets[i])) == false)
	{
		sendAll(ERR_USERNOTINCHANNEL(command.getSource()->getNName(), targets[i], command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 441" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->isOperator(server.getUser(targets[i])) == true)
		server.getChan(command.getParams()[0])->removeOperator(server.getUser(targets[i]));	
	else
		server.getChan(command.getParams()[0])->removeUser(server.getUser(targets[i]));
	std::string	message_chan = std::string(":") + SERVERNAME + " @" + command.getSource()->getNName() + " " + targets[i] + " " + command.getParams()[0] + " :User was kicked from channel";
	std::string message_kick = std::string(":") + SERVERNAME + " @" + command.getSource()->getNName() + " " + targets[i] + " " + command.getParams()[0] + " :You were kicked from channel";
	if (command.getParams().size() == 2)
	{
		message_kick += "\r\n";
		message_chan += "\r\n";
		sendAll(message_kick, *server.getUser(targets[i]));
		server.getChan(command.getParams()[0])->sendToChan(message_chan, "", command.getSource()->getNName());
		std::cout << message_chan << std::endl;
		std::cout << message_kick << std::endl;
	}
	else
	{
		message_kick += " :";
		message_chan += " :";
		for (size_t i = 2; i != command.getParams().size(); ++i)
		{
			if (!command.getParams()[i].empty())
			{
				message_chan += " " + command.getParams()[i];
				message_kick += " " + command.getParams()[i];
			}
		}
		message_kick += "\r\n";
		message_chan += "\r\n";
		sendAll(message_kick, *server.getUser(targets[i]));
		server.getChan(command.getParams()[0])->sendToChan(message_chan, "", command.getSource()->getNName());
		std::cout << message_chan << std::endl;
		std::cout << message_kick << std::endl;
	}
}

void	execute_KICK(Command& command, Server& server)
{
	if (command.getParams().empty() || command.getParams().size() < 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cout << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}

	std::vector<std::string>	targets = collect_arguments(command.getParams()[1]);
	if (targets.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_KICK(command, server, targets, i);
	}
}
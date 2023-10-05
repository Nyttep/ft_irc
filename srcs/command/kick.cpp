/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:32 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 19:07:10 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_KICK(Command &command, Server &server, std::vector<std::string> targets, size_t i)
{
	if (correct_nick(targets[i]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.isUser(targets[i]) == false)
	{
		sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[0])->onChannel(server.getUser(targets[i])) == false)
	{
		sendAll(ERR_USERNOTINCHANNEL(HOSTNAME, command.getSource()->getNName(), targets[i], command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 441" << std::endl;
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
			if (command.getParams()[2].length() > KICKLEN)
				command.getParams()[2].erase(KICKLEN, command.getParams()[2].length() - KICKLEN);
			message = std::string(" :") + command.getParams()[2];
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
		std::cout << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
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
	if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	std::vector<std::string>	targets = collect_arguments(command.getParams()[1]);
	if (targets.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_KICK(command, server, targets, i);
	}
}
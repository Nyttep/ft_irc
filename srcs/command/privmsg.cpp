/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:03 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:31:36 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PRIVMSG(Command &command, Server &server, std::vector<std::string> targets, size_t i, std::string message)
{
	if (targets[i].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	std::string	prefix("");
	std::string analyse_target = targets[i];
	if (have_prefix(analyse_target[0]) == true)
	{
		analyse_target.erase(0, 1);
	}
	if (chantypes(analyse_target[0]) == true && correct_chan(analyse_target) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, targets[i]), *command.getSource());
		return ;
	}
	if (chantypes(analyse_target[0]) == false && correct_nick(analyse_target) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
		return ;
	}
	if (chantypes(analyse_target[0]) == true)
	{
		if (server.chanExist(analyse_target) == false)
		{
			sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
			return ;
		}
		server.getChan(analyse_target)->sendToChan(US_PRIVMSG(setUserAddress(*command.getSource()), targets[i], message), prefix, command.getSource()->getNName());
	}
	else
	{
		if (server.isUser(targets[i]) == false)
		{
			sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
			return ;
		}
		sendAll(US_PRIVMSG(setUserAddress(*command.getSource()), targets[i], message), *server.getUser(targets[i]));
	}
}

void	execute_PRIVMSG(Command &command, Server &server)
{
	if (command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NORECIPIENT(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return;
	}
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParams()[0]);
	if (targets.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		return ;
	}
	if (command.getParams().size() < 2 || command.getParams()[1].empty())
	{
		sendAll(ERR_NOTEXTTOSEND(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		return ;
	}
	std::string message = command.getParams()[1];
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_PRIVMSG(command, server, targets, i, message);
	}
}
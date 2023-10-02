/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:03 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 17:02:33 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PRIVMSG(Command &command, Server &server, std::vector<std::string> targets, size_t i, std::string message)
{
	std::string	prefix;
	if (have_prefix(targets[i][0]) == true)
	{
		prefix = targets[i].substr(0, 1);
		targets[i].erase(0, 1);
	}
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), targets[i]), command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (chantypes(targets[i][0]) == true)
	{
		if (server.chanExist(targets[i]) == false)
		{
			sendAll(ERR_NOSUCHCHANNEL(command.getSource()->getNName(), targets[i]), command.getSource());
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
		std::string	nick;
		if (server.getChan(channels[i]).isOperator(command.getSource()) == true)
			nick = "@" + command.getSource()->getNName();
		else
			nick = command.getSource()->getNName();
		std::string f_message = ":" + nick + " " + targets[i] + " :" + message;
		server.getChan(targets[i]).sendToChan(f_message, prefix);
	}
	else
	{
		if (server.isUser(targets[i]) == false)
		{
			sendAll(ERR_NOSUCHNICK(command.getSource()->getNName(), targets[i]), command.getSource());
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
		std::string	nick;
		if (server.getChan(channels[i]).isOperator(command.getSource()) == true)
			nick = "@" + command.getSource()->getNName();
		else
			nick = command.getSource()->getNName();
		std::string f_message = ":" + nick + " " + targets[i] + " :" + message;
		sendAll(f_message, server.getUser(targets[i]));
	}
}

void	execute_PRIVMSG(Command &command, Server &server)
{
   if (command.getParams().empty() || command.getParams().size() < 2)
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0].empty())
	{
		sendAll(ERR_NORECIPIENT(command.getSource()->getNName(), command.getVerb()), command.getSource());
		std::cerr << "Redirection 411" << std::endl;
		return;
	}
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParams()[0]);
	if (targets.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(command.getSource()->getNName(), command.getParams()[0]), command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	std::string message = store_message(command);
	if (message.empty())
	{
		sendAll(ERR_NOTEXTTOSEND(command.getSource()->getNName()), command.getSource());
		std::cerr << "Redirection 412" << std::endl;
		return ;
	}
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_PRIVMSG(command, server, targets, i, message);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:03 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 10:54:23 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PRIVMSG(Command &command, Server &server, std::vector<std::string> targets, size_t i, std::string message)
{
	std::string	prefix("");
	std::cout << "ma target sera :" << targets[i] << std::endl;
	if (have_prefix(targets[i][0]) == true)
	{
		std::cout << "Je suis passe par la" << std::endl;
		prefix = targets[i].substr(0, 1);
		targets[i].erase(0, 1);
	}
	if (correct_nick_chan(targets[i]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(setUserAddress(*command.getSource()), command.getSource()->getNName(), targets[i]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (chantypes(targets[i][0]) == true)
	{
		std::cout << "c'est un chan" << std::endl;
		if (server.chanExist(targets[i]) == false)
		{
			sendAll(ERR_NOSUCHCHANNEL(setUserAddress(*command.getSource()), command.getSource()->getNName(), targets[i]), *command.getSource());
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
		std::string	nick;
		nick = setUserAddress(*command.getSource());
		std::string f_message = ":" + setUserAddress(*command.getSource()) + " " + command.getVerb() + " " + targets[i] + " :" + message + "\r\n";
		// sendAll(f_message, *command.getSource());
		std::cout << f_message << std::endl;
		server.getChan(targets[i])->sendToChan(f_message, prefix, command.getSource()->getNName());
	}
	else
	{
		std::cout << "c'est un user" << std::endl;
		if (server.isUser(targets[i]) == false)
		{
			sendAll(ERR_NOSUCHNICK(setUserAddress(*command.getSource()), command.getSource()->getNName(), targets[i]), *command.getSource());
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
		std::string	nick = setUserAddress(*command.getSource());
		std::string f_message = std::string(":") + nick + " " + command.getVerb() + " " + targets[i] + " :" + message + "\r\n";
		std::cout << f_message << std::endl;
		sendAll(f_message, *server.getUser(targets[i]));
	}
}

void	execute_PRIVMSG(Command &command, Server &server)
{
   if (command.getParams().empty() || command.getParams().size() < 2)
	{
		sendAll(ERR_NEEDMOREPARAMS(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0].empty())
	{
		sendAll(ERR_NORECIPIENT(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 411" << std::endl;
		return;
	}
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParams()[0]);
	if (targets.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(setUserAddress(*command.getSource()), command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	std::string message = store_message(command);
	if (message.empty())
	{
		sendAll(ERR_NOTEXTTOSEND(setUserAddress(*command.getSource()), command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 412" << std::endl;
		return ;
	}
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_PRIVMSG(command, server, targets, i, message);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:03 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 11:34:06 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_PRIVMSG(Command &command, Server &server, std::vector<std::string> targets, size_t i, std::string message)
{
	if (targets[i].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cout << "Redirection 461" << std::endl;
		return ;
	}
	std::string	prefix("");
	std::string analyse_target = targets[i];
	std::cout << "ma target sera :" << analyse_target << std::endl;
	if (have_prefix(analyse_target[0]) == true)
	{
		std::cout << "Je suis passe par la" << std::endl;
		analyse_target.erase(0, 1);
	}
	if (correct_nick_chan(analyse_target) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (chantypes(analyse_target[0]) == true)
	{
		std::cout << "c'est un chan" << std::endl;
		if (server.chanExist(analyse_target) == false)
		{
			sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
		server.getChan(analyse_target)->sendToChan(US_PRIVMSG(setUserAddress(*command.getSource()), targets[i], message), prefix, command.getSource()->getNName());
	}
	else
	{
		std::cout << "c'est un user" << std::endl;
		if (server.isUser(targets[i]) == false)
		{
			sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), targets[i]), *command.getSource());
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
		sendAll(US_PRIVMSG(setUserAddress(*command.getSource()), targets[i], message), *server.getUser(targets[i]));
	}
}

void	execute_PRIVMSG(Command &command, Server &server)
{
   if (command.getParams().empty() || command.getParams().size() < 2)
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0].empty())
	{
		sendAll(ERR_NORECIPIENT(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 411" << std::endl;
		return;
	}
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParams()[0]);
	if (targets.size() > targmax(command.getVerb()))
	{
		sendAll(ERR_TOOMANYTARGETS(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 407" << std::endl;
		return ;
	}
	std::string message = store_message(command);
	if (message.empty())
	{
		sendAll(ERR_NOTEXTTOSEND(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 412" << std::endl;
		return ;
	}
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_PRIVMSG(command, server, targets, i, message);
	}
}
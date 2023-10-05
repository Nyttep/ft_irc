/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:18:41 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 18:41:57 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	multiple_NOTICE(Command &command, Server &server, std::vector<std::string> targets, size_t i, std::string message)
{
	if (targets[i].empty())
		return ;
	std::string	prefix("");
	std::string analyse_target = targets[i];
	std::cout << "ma target sera :" << analyse_target << std::endl;
	if (have_prefix(analyse_target[0]) == true)
		analyse_target.erase(0, 1);
	if (chantypes(analyse_target[0]) == true && correct_chan(analyse_target) == false)
		return ;
	if (chantypes(analyse_target[0]) == false && correct_nick(analyse_target) == false)
		return ;
	if (chantypes(analyse_target[0]) == true)
	{
		if (server.chanExist(analyse_target) == false)
			return ;
		server.getChan(analyse_target)->sendToChan(US_NOTICE(setUserAddress(*command.getSource()), targets[i], message), prefix, command.getSource()->getNName());
	}
	else
	{
		if (server.isUser(targets[i]) == false)
			return ;
		sendAll(US_NOTICE(setUserAddress(*command.getSource()), targets[i], message), *server.getUser(targets[i]));
	}
}

void	execute_NOTICE(Command &command, Server &server)
{
   if (command.getParams().empty() || command.getParams().size() < 2)
		return ;
	if (command.getParams()[0].empty())
		return;
	std::vector<std::string>	targets;
	targets = collect_arguments(command.getParams()[0]);
	if (targets.size() > targmax(command.getVerb()))
		return ;
	std::string message = store_message(command);
	if (message.empty())
		return ;
	for (size_t i = 0; i != targets.size(); ++i)
	{
		multiple_NOTICE(command, server, targets, i, message);
	}
}
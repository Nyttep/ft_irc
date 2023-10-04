/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:13 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 10:55:26 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_USER(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 4 || command.getParams()[0].empty() || command.getParams()[1].empty() || command.getParams()[2].empty() || command.getParams()[3].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0].length() > USERLEN)
	{
		command.setPParams(0, command.getParams()[0].erase(USERLEN, command.getParams()[0].length() - USERLEN));
	}
	// std::string hostname = command.getSource()->getNName() + "!" + command.getSource()->getNName() + "@" + command.getParams()[2];
	// std::cout << hostname << std::endl;
	// command.getSource()->setHName(hostname);
	command.getSource()->setHName(command.getParams()[2]);
	std::string real_name;
	for (size_t i = 3; i < command.getParams().size(); ++i)
	{
		if (!command.getParams()[i].empty())
		{
			if (!real_name.empty())
				real_name += " ";
			real_name += (command.getParams()[i]);
		}
	}
	if (command.getSource()->getUName().empty())
		command.getSource()->setUName(command.getParams()[0]);
	command.getSource()->setRName(real_name);
	if (command.getSource()->getRegistered() == false && !command.getSource()->getNName().empty() \
		&& !command.getSource()->getUName().empty() && !command.getSource()->getRName().empty())
	{
		command.getSource()->setRegistered(true);
		handshake(command, server);
	}
}
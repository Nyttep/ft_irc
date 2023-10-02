/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:13 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 18:59:08 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_USER(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 4 || command.getParams()[0].empty() || command.getParams()[1].empty() || command.getParams()[2].empty() || command.getParams()[3].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[1] != "0" && command.getParams()[2] != "*")
	{
		sendAll(ERR_UNKNOWNERROR(command.getSource()->getNName(), command.getVerb(), " :0 * required\r\n"), *command.getSource());
		std::cerr << "Redirection 400" << std::endl;
	}
	if (command.getParams()[0].length() > USERLEN)
	{
		command.setPParams(0, command.getParams()[0].erase(USERLEN, command.getParams()[0].length() - USERLEN));
	}
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
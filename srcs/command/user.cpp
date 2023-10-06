/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:13 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:42:11 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_USER(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 4 || command.getParams()[0].empty() \
		|| command.getParams()[1].empty() || command.getParams()[2].empty() || command.getParams()[3].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (command.getParams()[0].length() > USERLEN)
	{
		command.setPParams(0, command.getParams()[0].erase(USERLEN, command.getParams()[0].length() - USERLEN));
	}
	if (command.getSource()->getUName().empty())
		command.getSource()->setUName(command.getParams()[0]);
	command.getSource()->setHName(HOSTNAME);
	command.getSource()->setRName(command.getParams()[3]);
	if (command.getSource()->getRegistered() == false && !command.getSource()->getNName().empty() \
		&& !command.getSource()->getUName().empty() && !command.getSource()->getRName().empty() \
		&& !command.getSource()->getHName().empty())
	{
		command.getSource()->setRegistered(true);
		handshake(command, server);
	}
}
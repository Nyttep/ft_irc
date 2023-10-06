/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:18 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:29:00 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_INVITE(Command &command, Server &server)
{
	if (command.getParams().empty())
	{
		server.listInvite(command);
		return ;
	}
	if (command.getParams().size() < 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (correct_nick(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (correct_chan(command.getParams()[1]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[1]), *command.getSource());
		return ;
	}	
	if (server.chanExist(command.getParams()[1]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[1]), *command.getSource());
		return;
	}
	if (server.getChan(command.getParams()[1])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[1]), *command.getSource());
		return ;
	}
	if ((server.getChan(command.getParams()[1])->getI() == true) && (server.getChan(command.getParams()[1])->isOperator(command.getSource()) == false))
	{
		sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[1]), *command.getSource());
		return ;
	}
	if (server.isUser(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[1])->onChannel(server.getUser(command.getParams()[0])) == true)
	{
		sendAll(ERR_USERONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], command.getParams()[1]), *command.getSource());
		return ;
	}
	if (server.getChan(command.getParams()[1])->isInvite(server.getUser(command.getParams()[0])) == false)
		server.getChan(command.getParams()[1])->addInvite(server.getUser(command.getParams()[0]));
	sendAll(RPL_INVITING(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], command.getParams()[1]), *command.getSource());
	sendAll(US_INVITE(setUserAddress(*command.getSource()), command.getParams()[0], command.getParams()[1]), *server.getUser(command.getParams()[0]));
	return;
}
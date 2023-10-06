/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:10 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:31:50 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_TOPIC(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (correct_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[0]), *command.getSource());
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		return ;
	}
	if (command.getParams().size() == 1)
	{
		if (server.getChan(command.getParams()[0])->getTopic().empty())
		{
			sendAll(RPL_NOTOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		}
		else
		{
			sendAll(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], server.getChan(command.getParams()[0])->getTopic()), *command.getSource());
		}
	}
	else
	{
		
		if (server.getChan(command.getParams()[0])->getT() == true && server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
		{
			sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			return;
		}
		if (command.getParams()[1].empty())
		{
			server.getChan(command.getParams()[0])->setTopic("");
			server.getChan(command.getParams()[0])->sendToChan(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], ""), "", "");
		}
		else
		{
			std::string	msg = command.getParams()[1];
			if (command.getParams()[1].length() > TOPICLEN)
				msg.erase(TOPICLEN, msg.length() - TOPICLEN);
			server.getChan(command.getParams()[0])->setTopic(msg);
			server.getChan(command.getParams()[0])->sendToChan(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], server.getChan(command.getParams()[0])->getTopic()), "", "");
		}
	}
}
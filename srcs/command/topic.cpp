/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:10 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 22:18:15 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_TOPIC(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (command.getParams().size() == 1)
	{
		if (server.getChan(command.getParams()[0])->getTopic().empty())
		{
			sendAll(RPL_NOTOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cout << "Redirection 331" << std::endl;
		}
		else
		{
			sendAll(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], server.getChan(command.getParams()[0])->getTopic()), *command.getSource());
			std::cout << "Redirection 332 suivi de 333(optionnel)" << std::endl;
		}
	}
	else
	{
		
		if (server.getChan(command.getParams()[0])->getT() == true && server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
		{
			sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cerr << "Redirection 482" << std::endl;
			return;
		}
		if (command.getParams()[1].empty())
		{
			server.getChan(command.getParams()[0])->setTopic("");
			server.getChan(command.getParams()[0])->sendToChan(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], ""), "", "");
		}
		else
		{
			std::cout << command.getParams()[1] << std::endl;
			if (command.getParams()[1].length() > TOPICLEN)
			{
				std::cout << "je rentre dans la condition" << std::endl;
				command.getParams()[1].erase(TOPICLEN, command.getParams()[1].length() - TOPICLEN);
					
			}
			std::cout << command.getParams()[1] << std::endl;
			server.getChan(command.getParams()[0])->setTopic(command.getParams()[1]);
			server.getChan(command.getParams()[0])->sendToChan(RPL_TOPIC(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], server.getChan(command.getParams()[0])->getTopic()), "", "");
		}
	}
}
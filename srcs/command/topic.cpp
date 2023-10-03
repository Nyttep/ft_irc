/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:10 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/03 15:04:02 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_TOPIC(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 1 || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (server.chanExist(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (server.getChan(command.getParams()[0])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (command.getParams().size() == 1)
	{
		std::string	nick;
		if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == true)
			nick = "@" + command.getSource()->getNName();
		else
			nick = command.getSource()->getNName();
		if (server.getChan(command.getParams()[0])->getTopic().empty())
		{
			sendAll(RPL_NOTOPIC(nick, command.getParams()[0]), *command.getSource());
			std::cout << "Redirection 331" << std::endl;
		}
		else
		{
			sendAll(RPL_TOPIC(nick, command.getParams()[0], server.getChan(command.getParams()[0])->getTopic()), *command.getSource());;
			std::cout << "Redirection 332 suivi de 333(optionnel)" << std::endl;
		}
	}
	else
	{
		if (server.getChan(command.getParams()[0])->getT() == true && server.getChan(command.getParams()[0])->isOperator(command.getSource()) == false)
		{
			sendAll(ERR_CHANPRIVSNEEDED(command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cerr << "Redirection 482" << std::endl;
			return;
		}
		std::string new_topic;
		for (size_t i = 1; i <= command.getParams().size(); ++i)
		{
	 		if (!command.getParams()[i].empty())
	   		{
				if (!new_topic.empty())
					new_topic += " ";
				new_topic += (command.getParams()[i]);
			}
		}
		if (new_topic.empty())
			server.getChan(command.getParams()[0])->setTopic("");
		else
			server.getChan(command.getParams()[0])->setTopic(new_topic);
		std::string	nick;
		if (server.getChan(command.getParams()[0])->isOperator(command.getSource()) == true)
			nick = "@" + command.getSource()->getNName();
		else
			nick = command.getSource()->getNName();
		std::string f_message = std::string(":") + SERVERNAME + " " + nick + " " + command.getParams()[0] + " :Topic changed :" + server.getChan(command.getParams()[0])->getTopic() + "\r\n";
		sendAll(f_message, *command.getSource());
		server.getChan(command.getParams()[0])->sendToChan(f_message, "", command.getSource()->getNName());
	}
}
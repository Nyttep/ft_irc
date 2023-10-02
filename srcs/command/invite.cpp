/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:18 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 17:02:33 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_INVITE(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams().size() < 2 || \
		command.getParams()[0].empty() || command.getParams()[1].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), command.getSource());
		std::cout << "Redirection 461" << std::endl;
		return ;
	}
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), command.getParams()[0]), command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (correct_nick_chan(command.getParams()[1]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(command.getSource()->getNName(), command.getParams()[1]), command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}	
	if (server.chanExist(command.getParams()[1]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(command.getSource()->getNName(), command.getParams()[1]), command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (server.getChan(command.getParams()[1]).onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(command.getSource()->getNName(), command.getParams()[1]), command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[1]).isOperator(command.getSource()) == false)
	{
		sendAll(ERR_CHANPRIVSNEEDED(command.getSource()->getNName(), command.getSource()->getNName()), command.getSource());
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	if (server.isUser(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHNICK(command.getSource()->getNName(), command.getParams()[0]), command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[1]).onChannel(server.getUser(command.getParams()[0])) == true)
	{
		sendALL(ERR_USERONCHANNEL(command.getSource()->getNName(), command.getParams()[0], command.getParams()[1]), command.getSource());
		std::cerr << "Redirection 443" << std::endl;
		return ;
	}
	server.getChan(command.getParams()[1]).addInvite(server.getUser(command.getParams()[0]));
	std::string	nick;
	if (server.getChan(command.getParams()[1]).isOperator(command.getSource()) == true)
		nick = "@" + command.getSource()->getNName();
	else
		nick = command.getSource()->getNName();
	sendAll(RPL_INVITING(nick, command.getParams()[0], command.getParams()[1]), command.getSource());
	sendAll(":" + SERVERNAME + " " + server.getUser(command.getParams()[0]).getNName() + " " + command.getParams()[1] + " :You are invited to this channel\r\n", server.getUser(command.getParams()[0]));
	std::cout << "Redirection 341 à User command et message invite pour la cible" << std::endl;
	return;
}
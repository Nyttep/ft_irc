/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:18 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/05 18:51:06 by mportrai         ###   ########.fr       */
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
		std::cout << "Redirection 461" << std::endl;
		return ;
	}
	if (chantypes(command.getParams()[0][0]) == true || correct_nick(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (chantypes(command.getParams()[1][0]) == false || correct_chan(command.getParams()[1]) == false)
	{
		sendAll(ERR_BADCHANMASK(HOSTNAME, command.getParams()[1]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}	
	if (server.chanExist(command.getParams()[1]) == false)
	{
		sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[1]), *command.getSource());
		std::cerr << "Redirection 403" << std::endl;
		return;
	}
	if (server.getChan(command.getParams()[1])->onChannel(command.getSource()) == false)
	{
		sendAll(ERR_NOTONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[1]), *command.getSource());
		std::cerr << "Redirection 442" << std::endl;
		return ;
	}
	if ((server.getChan(command.getParams()[1])->getI() == true) && (server.getChan(command.getParams()[1])->isOperator(command.getSource()) == false))
	{
		sendAll(ERR_CHANPRIVSNEEDED(HOSTNAME, command.getSource()->getNName(), command.getParams()[1]), *command.getSource());
		std::cerr << "Redirection 482" << std::endl;
		return ;
	}
	if (server.isUser(command.getParams()[0]) == false)
	{
		sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 401" << std::endl;
		return ;
	}
	if (server.getChan(command.getParams()[1])->onChannel(server.getUser(command.getParams()[0])) == true)
	{
		sendAll(ERR_USERONCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], command.getParams()[1]), *command.getSource());
		std::cerr << "Redirection 443" << std::endl;
		return ;
	}
	server.getChan(command.getParams()[1])->addInvite(server.getUser(command.getParams()[0]));
	sendAll(RPL_INVITING(HOSTNAME, command.getSource()->getNName(), command.getParams()[0], command.getParams()[1]), *command.getSource());
	sendAll(US_INVITE(setUserAddress(*command.getSource()), command.getParams()[0], command.getParams()[1]), *server.getUser(command.getParams()[0]));
	std::cout << "Redirection 341 à User command et message invite pour la cible" << std::endl;
	return;
}
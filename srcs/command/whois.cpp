/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:05:29 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 15:12:31 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_WHOIS(Command &command, Server &server)
{
	if (correct_nick_chan(command.getParams()[0]) == false)
	{
		sendAll(ERR_ERRONEUSNICKNAME(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (chantypes(command.getParams()[0][0]) == true)
	{
		if (server.chanExist(command.getParams()[0]) == false)
		{
			sendAll(ERR_NOSUCHCHANNEL(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
	}
	else
	{
		if (server.isUser(command.getParams()[0]) == false)
		{
			sendAll(ERR_NOSUCHNICK(HOSTNAME, command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
		sendAll(RPL_WHOISUSER(HOSTNAME, command.getSource()->getNName(), command.getSource()->getNName(), command.getSource()->getUName(), command.getSource()->getHName(), command.getSource()->getRName()), *command.getSource());
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:31:04 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 10:55:43 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_WHO(Command &command, Server &server)
{
	if (correct_nick_chan(command.getParams()[0]))
	{
		sendAll(ERR_ERRONEUSNICKNAME(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
		std::cerr << "Redirection 432" << std::endl;
		return ;
	}
	if (chantypes(command.getParams()[0][0]) == true)
	{
		if (server.chanExist(command.getParams()[0]) == false)
		{
			sendAll(ERR_NOSUCHCHANNEL(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cerr << "Redirection 403" << std::endl;
			return ;
		}
	}
	else
	{
		if (server.isUser(command.getParams()[0]) == false)
		{
			sendAll(ERR_NOSUCHNICK(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getParams()[0]), *command.getSource());
			std::cerr << "Redirection 401" << std::endl;
			return ;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:53 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/04 10:52:38 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_PASS(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(setUserAddress(*command.getSource()), command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return ;
	}
	if (command.getParams()[0] != server.getPswd())
	{
		command.getSource()->setPass(false);
		if (command.getSource()->getNName().empty())
			sendAll(ERR_PASSWDMISMATCH("guest", command.getSource()->getNName()), *command.getSource());
		else
			sendAll(ERR_PASSWDMISMATCH(setUserAddress(*command.getSource()), command.getSource()->getNName()), *command.getSource());
		std::cerr << "Redirection 464" << std::endl;
		return ;
	}
	command.getSource()->setPass(true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:53 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 11:42:05 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_PASS(Command &command, Server &server)
{
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(HOSTNAME, command.getSource()->getNName(), command.getVerb()), *command.getSource());
		return ;
	}
	if (command.getParams()[0] != server.getPswd())
	{
		command.getSource()->setPass(false);
		sendAll(ERR_PASSWDMISMATCH(HOSTNAME, command.getSource()->getNName()), *command.getSource());
		return ;
	}
	command.getSource()->setPass(true);
}
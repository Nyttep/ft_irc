/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:07 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/03 12:52:34 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	disconnectUser(Command& cmd, Server& serv)
{
	close(cmd.getSource()->getFD());
	serv.delFromPfds(cmd.getSource()->getFD());
	serv.removeUser(cmd.getSource()->getFD());
}

void	execute_QUIT(Command &command, Server& serv)
{
	std::string	message = "Quit:";
	if (command.getParams().empty())
		message += " Disconnecting from IRC Server";
	else
	{
		for (size_t i = 0; i < command.getParams().size(); ++i)
		{
			if (!command.getParams()[i].empty())
				message += " " + command.getParams()[i];
		}
	}
	command.getSource()->leaveAllChan(command);
	disconnectUser(command, serv);
}
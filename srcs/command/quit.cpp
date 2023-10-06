/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:07 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/06 19:32:36 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_QUIT(Command &command, Server& serv)
{
	std::string	message;
	if (command.getParams().empty())
		message = ":Disconnecting from IRC Server";
	else
		message += std::string(":") + command.getParams()[0];
	command.getSource()->sendToAllChan(US_QUIT(setUserAddress(*command.getSource()), message));
	command.getSource()->leaveAllChan(serv);
	sendAll(RPL_ERROR(HOSTNAME, ":Quit command"), *command.getSource());
	int	fd = command.getSource()->getFD();
	serv.delFromPfds(fd);
	serv.removeUser(fd);
	close(fd);
}
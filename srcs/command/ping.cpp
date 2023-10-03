/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mportrai <mportrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:57 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/03 15:23:00 by mportrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_PING(Command &command)
{
	if (command.getParams().empty() || command.getParams()[0].empty())
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return;
	}
	std::string PONG = std::string(":") + command.getSource()->getNName() + " PONG " + SERVERNAME + " " + command.getParams()[0] + "\r\n";
	sendAll(PONG, *command.getSource());
}
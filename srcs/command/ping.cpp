/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:41:57 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 18:45:59 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_PING(Command &command)
{
	if (command.getParams().empty() || command.getParams()[0].empty() || command.getParams().size() != 1)
	{
		sendAll(ERR_NEEDMOREPARAMS(command.getSource()->getNName(), command.getVerb()), *command.getSource());
		std::cerr << "Redirection 461" << std::endl;
		return;
	}
	std::string PONG = std::string(":") + SERVERNAME + " " + command.getSource()->getNName() + ":PONG " + SERVERNAME + " " + command.getParams()[0];
	sendAll(PONG, *command.getSource());
}
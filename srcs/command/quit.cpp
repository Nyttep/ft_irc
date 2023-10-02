/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:42:07 by mportrai          #+#    #+#             */
/*   Updated: 2023/10/02 18:50:01 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	execute_QUIT(Command &command)
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
	// fonction de deco d'un utilisateur
}
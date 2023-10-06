/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:09:42 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/21 16:09:42 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	g_sig = 0;

int	main(int argc, char** argv)
{
	struct sigaction sa;

	try
	{
		if (signals(sa))
			return (1);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
	if (argc != 3)
	{
		std::cerr << "Error: Port and password required" << std::endl;
		exit(1);
	}
	ft_check_arg(argv);
	try
	{
		Server	serv(argv[2], argv[1]);
		int	listener = getListenerSocket(serv);
		if (listener < 0)
		{
			std::cerr << "Error: could not initialize listener socket\n";
			serv.~Server();
			exit(1);
		}
		serv.initPfds(listener);
		try
		{
			serverLoop(listener, serv);
		}
		catch(const std::exception& e)
		{
			serv.allUsersMessage(RPL_ERROR(HOSTNAME, ":Server crashed on a fatal error"));
			closeAll(serv.getPfds(), serv.getFDCount());
			serv.~Server();
			std::cerr << e.what() << '\n';
			exit(1);
		}
		
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

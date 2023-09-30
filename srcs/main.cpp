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


int	main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cerr << "Error: Port and password required" << std::endl;
		exit(1);
	}
	ft_check_arg(argc, argv);
	Server	serv(argv[2], argv[1]);
	int	listener = getListenerSocket(serv);
	if (listener < 0)
	{
		std::cerr << "Error: could not initialize listener socket\n";
		return (1);
	}
	std::vector<struct pollfd>	pfds = getPfds(listener);
	serverLoop(listener, pfds, serv);
	return (0);
}

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
#include "Server.hpp"

int	getListenerSocket(Server serv)
{
	int	listener;
	int	yes = 1;
	int	errCode;
	struct addrinfo	hints, *ai, *p;

	std::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	errCode = getaddrinfo(NULL, serv.getPort(), &hints, &ai);
	if (errCode != 0)
	{
		std::cerr << "Error: getaddrinfo: " << gai_strerror(errCode) << "\n";
		exit(1);
	}
	for (p = se)
}

std::vector	getPfds()
{

}

int	main(int argc, char** argv)
{
	Server	serv(argv[2], argv[1]);
	int	listener = getListenerSocket(serv);
	return (0);
}
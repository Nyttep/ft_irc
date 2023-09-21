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
	int	listener = -1;
	int	yes = 1;
	int	errCode;
	struct addrinfo	hints, *ai;

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
	for (struct addrinfo *p = ai; p != NULL; p = p->ai_next)
	{
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0)
			continue;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(listener);
			listener = -1;
			continue;
		}
		break;
	}
	freeaddrinfo(ai);
	if (listener < 0)
		return (-1);
	if (listen(listener, 10) == -1)
		return (-1);
	return (listener);
}

std::vector<struct pollfd>	getPfds(int listener)
{
	std::vector<struct pollfd>	pfds;
	struct pollfd				listenerStruct;

	pfds.push_back(listenerStruct);
	pfds[0].fd = listener;
	pfds[0].events = POLLIN;
	return (pfds);
}

int	main(int argc, char** argv)
{
	Server	serv(argv[2], argv[1]);
	int	listener = getListenerSocket(serv);
	if (listener < 0)
	{
		std::cerr << "Error: could not initialize listener socket\n";
		return (1);
	}
	std::vector<struct pollfd>	pfds = getPfds(listener);
	return (0);
}
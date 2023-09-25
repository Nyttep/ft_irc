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

	std::memset(&hints, 0, sizeof(hints));
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

struct pollfd	addToPfds(int newFD, int& fdCount)
{
	struct pollfd			newPollFD;

	newPollFD.fd = newFD;
	newPollFD.events = POLLIN;
	fdCount++
	return (newPollFD);
}

void	delFromPfds(std::vector<struct pollfd> pfds, int i, int& fdCount)
{
	pfds[i] = pfds[fdCount - 1];
	fdCount--;
}

std::string	formatRecvData(std::string buff, std::string  cmd)
{
	for (int i = 0; )
	return (cmd);
}

void	serverLoop(int listener, std::vector<struct pollfd> pfds, Server serv)
{
	int						fdCount = 1;
	struct sockaddr_storage	remoteAddr
	socklen_t				addrLen;
	int						newFD;
	User*					client;

	buff.resize(SIZE_BUFF);
	while (true)
	{
		int pollCount = poll(pfds, fdCount, -1);
		if (pollCount == -1)
		{
			perror("Error: poll: ");
			exit(1);
		}
		for (int i = 0; i < fdCount; i++)
		{
			if (pfds[i].revents & POLLIN)
			{
				if (pfds[i].fd == listener)
				{
					addrLen = sizeof(remoteAddr);
					newFD = accept(listener, (struct sockaddr *)&remoteAddr, &addrAen);
					if (newFD == -1)
					{
						perror("Error: Accept: ");
					}
					else
					{
						pfds[fdCount] = addToPfds(newFD, fdCount);
						std::cout << "server: new connection on socket " << newFD << std::endl;
					}
				}
				else
				{
					if (serv.isRegistered(pfds[i].fd))
					{
						client = serv.getUser(pfds[i].fd);
					}
					else
					{
						if (serv.addUser(pfds[i].fd, User()))
						{

							return (1);
						}
						client = serv.getUser(pfds[i].fd);
					}
					int	nBytes = recv(pfds[i].fd, client.getBuff().c_str(), SIZE_BUFF, 0);
					if (nBytes <= 0)
					{
						if (nBytes == 0)
						{
							std::cout << "server: socket " << sender_fd << "hung up" << std::endl; //dire au serv
						}
						else
						{
							perror("Error: recv: ");
						}
						serv.removeUser(pfds[i].pfds);
						close (pfds[i].fd);
						delFromPfds(pfds, i, fd_count);
					}
					/*else if (isTooLong(client.getBuff()))
					{}*/ //treat msgs too long
					else
					{
						if (client.formatRecvData())
							//send cmd
						client.clearBuff();
						client.clearMsg();
					}
				}
			}
		}
	}
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
	serverLoop(pfds, listener, serv);
	return (0);
}
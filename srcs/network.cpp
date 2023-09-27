/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:11:29 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/25 18:11:29 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

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
	errCode = getaddrinfo(NULL, serv.getPort().c_str(), &hints, &ai);
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

	memset(&listenerStruct, 0, sizeof(listenerStruct));
	pfds.push_back(listenerStruct);
	pfds[0].fd = listener;
	pfds[0].events = POLLIN;
	return (pfds);
}

void	addToPfds(int newFD, int& fdCount, std::vector<struct pollfd>& pfds)
{
	struct pollfd			newPollFD;

	memset(&newPollFD, 0, sizeof(newPollFD));
	newPollFD.fd = newFD;
	newPollFD.events = POLLIN;
	fdCount++;
	pfds.push_back(newPollFD);
}

void	delFromPfds(std::vector<struct pollfd> pfds, int i, int& fdCount)
{
	pfds[i] = pfds[fdCount - 1];
	fdCount--;
}

bool	msgTooLong(std::string msg)
{
	if (msg.size() > 512)
		return (true);
	return (false);
}

bool	sendAll(std::string msg, User target)
{
	int	sent = 0;
	int len = msg.size();
	int bytesleft = len;
	while (total < len)
	{
		n = send(target, msg.data() + total, bytesleft, 0);
		if (n == -1)
			break;
		total += n;
		bytesleft -= n;
	}
	if (n == -1)
		return (0);
	return (1);
}

void	serverLoop(int listener, std::vector<struct pollfd> pfds, Server serv)
{
	int						fdCount = 1;
	struct sockaddr_storage	remoteAddr;
	socklen_t				addrLen;
	int						newFD;
	std::vector<char>		buff(SIZE_BUFF);
	User*					client;

	while (true)
	{
		int pollCount = poll(pfds.data(), fdCount, -1);
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
					newFD = accept(listener, (struct sockaddr *)&remoteAddr, &addrLen);
					if (newFD == -1)
					{
						perror("Error: Accept: ");
					}
					else
					{
						addToPfds(newFD, fdCount, pfds);
						std::cout << "server: new connection on socket " << newFD << std::endl;
					}
				}
				else
				{
					if (serv.isRegistered(pfds[i].fd))
					{
						client = &(serv.getUser(pfds[i].fd));
					}
					else
					{
						if (!serv.addUser(pfds[i].fd, User(pfds[i].fd)))
						{
							std::cerr << "Error: unexpected error: couldn't insert element in map";
							return ;
						}
						client = &(serv.getUser(pfds[i].fd));
					}
					std::fill(buff.begin(), buff.end(), 0);
					int	nBytes = recv(pfds[i].fd, buff.data(), SIZE_BUFF, 0);
					std::cout << "buff = " << buff.data();
					if (nBytes <= 0)
					{
						if (nBytes == 0)
						{
							std::cout << "server: socket " << pfds[i].fd << "hung up" << std::endl; //dire au serv
						}
						else
						{
							perror("Error: recv: ");
						}
						serv.removeUser(pfds[i].fd);
						close (pfds[i].fd);
						delFromPfds(pfds, i, fdCount);
					}
					else
					{
						if (client->formatRecvData(buff))
						{
							if (msgTooLong(client->getMsg))
							{
								if(!sendAll(ERR_INPUTTOOLONG(client->getFD()), *client))
								{
									perror("Error: ");
									return ;
								}
							}
							std::cout << pfds[i].fd << "sent: " << client->getMsg() << std::endl;//send cmd
							client->clearMsg();
						}
					}
				}
			}
		}
	}
}

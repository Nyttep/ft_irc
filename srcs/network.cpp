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

int	getListenerSocket(Server &serv)
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

void	addToPfds(int newFD, int& fdCount, std::vector<struct pollfd>& pfds)
{
	struct pollfd			newPollFD;

	std::memset(&newPollFD, 0, sizeof(newPollFD));
	newPollFD.fd = newFD;
	newPollFD.events = POLLIN;
	fdCount++;
	pfds.push_back(newPollFD);
}

// void	delFromPfds(std::vector<struct pollfd> pfds, int i, int& fdCount)
// {
	// pfds[i] = pfds[fdCount - 1];
	// fdCount--;
// }

bool	msgTooLong(std::string msg)
{
	if (msg.size() > 512)
		return (true);
	return (false);
}

bool	sendAll(std::string msg, User &target)
{
	int	sent = 0;
	int len = msg.size();
	int bytesleft = len;
	int n = 0;

	while (sent < len)
	{
		n = send(target.getFD(), msg.data() + sent, bytesleft, 0);
		if (n == -1)
			break;
		sent += n;
		bytesleft -= n;
	}
	if (n == -1)
		return (0);
	return (1);
}

void	closeAll(std::vector<struct pollfd> pfds, int& fdCount)
{
	for (int i = 0; i < fdCount; i++)
		close (pfds[i].fd);
}


void	serverLoop(int listener, Server& serv)
{
	struct sockaddr_storage	remoteAddr;
	socklen_t				addrLen;
	int						newFD;
	std::vector<char>		buff(SIZE_BUFF);
	User*					client;
	int						ret = -1;
	int						oldFDCount = 0;

	while (true)
	{
		if (g_sig != 0)
		{
			if (g_sig == SIGINT)
				std::cerr << "received SIGINT\nshuting down the server";
			if (g_sig == SIGQUIT)
				std::cerr << "received SIGQUIT\nshuting down the server";
			closeAll(serv.getPfds(), serv.getFDCount());
			return ;
		}
		int pollCount = poll(serv.getPfds().data(), serv.getFDCount(), -1);
		if (g_sig != 0)
		{
			if (g_sig == SIGINT)
				std::cerr << "received SIGINT\nshuting down the server";
			if (g_sig == SIGQUIT)
				std::cerr << "received SIGQUIT\nshuting down the server";
			closeAll(serv.getPfds(), serv.getFDCount());
			return ;
		}
		if (pollCount == -1)
		{
			std::perror("Error: poll: ");
			closeAll(serv.getPfds(), serv.getFDCount());
			return ;
		}
		for (int i = 0; i < serv.getFDCount() && pollCount > 0 ; i++)
		{
			if (serv.getPfds()[i].revents & POLLIN)
			{
				if (serv.getPfds()[i].fd == listener)
				{
					addrLen = sizeof(remoteAddr);
					newFD = accept(listener, (struct sockaddr *)&remoteAddr, &addrLen);
					if (newFD == -1)
					{
						std::perror("Error: Accept: ");
						closeAll(serv.getPfds(), serv.getFDCount());
						return ;
					}
					else
					{
						addToPfds(newFD, serv.getFDCount(), serv.getPfds());
					}
				}
				else
				{
					if (serv.isRegistered(serv.getPfds()[i].fd))
					{
						client = serv.getUser(serv.getPfds()[i].fd);
					}
					else
					{
						if (!serv.addUser(serv.getPfds()[i].fd, new User(serv.getPfds()[i].fd)))
						{
							std::cerr << "Error: unexpected error: couldn't insert element in map";
							closeAll(serv.getPfds(), serv.getFDCount());
							return ;
						}
						client = serv.getUser(serv.getPfds()[i].fd);
					}
					int	nBytes = recv(serv.getPfds()[i].fd, buff.data(), SIZE_BUFF, 0);
					if (nBytes <= 0)
					{
						if (nBytes == 0)
						{
							std::cout << "server: socket " << serv.getPfds()[i].fd << "hung up" << std::endl; //dire au serv
						}
						else
						{
							std::perror("Error: recv: ");
						}
						serv.disconnectUser(serv.getPfds()[i].fd);
					}
					else
					{
						ret = client->formatRecvData(buff);
						std::fill(buff.begin(), buff.end(), 0);
						while (ret != EOT_NOT_FOUND)
						{
							if (msgTooLong(client->getMsg()))
							{
								if (client->getNName().empty())
								{
									sendAll(ERR_INPUTTOOLONG("guest"), *client);
								}
								else
								{
									sendAll(ERR_INPUTTOOLONG(client->getNName()), *client);
								}
							}
							oldFDCount = serv.getFDCount();
							parser(*client, client->getMsg(), serv);
							if (oldFDCount == serv.getFDCount())
							{
								client->clearMsg();
								ret = client->formatRecvData(buff);
							}
							else
							{
								ret = EOT_NOT_FOUND;	
							}
						}
					}
				}
				pollCount--;
			}
		}
	}
}

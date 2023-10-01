/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:12:12 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/21 17:12:12 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <algorithm>
# include <cstring>
# include <iostream>
# include <fstream>
# include <string>
# include <utility>
# include <map>
# include <vector>
# include <cstdlib>
# include <sys/types.h>
# include <sys/poll.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <signal.h>
# include "rpl_err_command.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"

# define SIZE_BUFF 1024

extern int g_sig;

int							getListenerSocket(Server serv);
std::vector<struct pollfd>	getPfds(int listener);
void						serverLoop(int listener, std::vector<struct pollfd> pfds, Server serv, int fdCount);
bool						sendAll(std::string msg, User &starget);

void						ft_check_arg(int argc, char **argv);
int							ft_atoi(const char *str);

int							signals(struct sigaction &sa);

#endif
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
# include "rpl_err_command.hpp"
# include "Message.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"

# define SIZE_BUFF 1024

int							getListenerSocket(Server serv);
std::vector<struct pollfd>	getPfds(int listener);
void						serverLoop(int listener, std::vector<struct pollfd> pfds, Server serv);
bool						sendAll(std::string msg, User target);

void	ft_check_arg(int argc, char **argv);
int		ft_atoi(const char *str);

#endif
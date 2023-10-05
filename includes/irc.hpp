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
# include <sstream>
# include <string>
# include <utility>
# include <map>
# include <vector>
# include <cstdlib>
# include <climits>
# include <ctime>
# include <sys/types.h>
# include <sys/poll.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <signal.h>
# include "Support.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "Server.hpp"
# include "Command.hpp"
# include "rpl_err_command.hpp"

# define SIZE_BUFF 10240
# define EOT_NOT_FOUND 0
# define FOUND_EXTRA 1
# define EOT 2

extern int g_sig;

void						disconnectUser(int fd, Server& serv);
int							getListenerSocket(Server &serv);
std::vector<struct pollfd>	getPfds(int listener);
void						serverLoop(int listener, Server &serv);
bool						sendAll(std::string msg, User &target);
void						closeAll(std::vector<struct pollfd> pfds, int& fdCount);

// check_arg
void						ft_check_arg(char **argv);
int							ft_atoi(const char *str);

void	parser(User& source, std::string reception, Server& server);

// command
void						execute_INVITE(Command& command, Server& server);
void						execute_JOIN(Command& command, Server& server);
void						execute_KICK(Command& command, Server& server);
void						execute_MODE(Command& command, Server& server);
void						execute_NICK(Command& command, Server& server);
void						execute_PART(Command& command, Server& server);
void						execute_PASS(Command& command, Server& server);
void						execute_PING(Command& command);
void						execute_PRIVMSG(Command& command, Server& server);
void						execute_QUIT(Command& command, Server& serv);
void						execute_TOPIC(Command& command, Server& server);
void						execute_USER(Command& command, Server& server);
void	                    execute_WHOIS(Command &command, Server &server);


// check_command
std::vector<std::string>	collect_arguments(std::string string);
bool                    	correct_nick_chan(std::string name);
std::string	                store_message(Command& command);
std::string                 empty_param(std::string param, size_t i);
bool	                    analyse_param(std::string param, Command &command);
void                        handshake(Command &command, Server &server);

int							signals(struct sigaction &sa);

#endif
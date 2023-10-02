/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdubois <pdubois@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:50:32 by pdubois           #+#    #+#             */
/*   Updated: 2023/09/20 17:50:32 by pdubois          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"

class Server //date creation ?
{
	private :
		std::string				_pswd;
		std::string				_port;
		std::map<int, User*>	_users;
		std::vector<Channel*>	_channels;
		Server();
	public :
		Server(std::string newPswd, std::string newPort);
		Server(const Server& toCopy);
		~Server();
		Server&		operator=(const Server& rhs);
		std::string	getPswd();
		bool		isValidPswd(std::string tryPswd);
		std::string	getPort();
		User&		getUser(int	key);
		User&		getUser(std::string name);
		bool		addUser(int key, User *value);
		bool		removeUser(int key);
		bool		isUser(std::string name);
		bool		isRegistered(int key);
		void		addChan(Channel	*newChan);
		bool		chanExist(std::string name);
		Channel&	getChan(std::string name);
		bool		nicknameCollision(std::string nickname);
		void		allUsersMessage(std::string message);
};

#endif
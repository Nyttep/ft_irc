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
		bool		addUser(int key, User *value);
		bool		removeUser(int key);
		bool		isRegistered(int key);
		void		addChan(Channel	*newChan);
		bool		chanExist(std::string name);
};

#endif
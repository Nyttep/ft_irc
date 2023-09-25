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
# include "Channel.hpp"
# include "User.hpp"

class Server //date creation ?
{
	private :
		std::string				_pswd;
		int						_port;
		std::map<int, User>		_users;
		std::vector<Channel>	_channels;
		Server();
	public :
		Server(std::string newPswd, int newPort);
		Server(const Server& toCopy);
		~Server();
		Server&		operator=(const Channel& rhs);
		std::string	getPswd();
		bool		isValidPswd(std::string try);
		int			getPort();
		User&		getUser(int	key);
		bool		addUser(int key, User value);
		bool		removeUser(int key);
		bool		isRegistered(int key);
		void		addChan(Channel	newChan);
		bool		chanExist(std::string name);
};

#endif